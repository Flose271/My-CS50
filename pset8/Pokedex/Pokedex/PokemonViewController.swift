import UIKit

class PokemonViewController: UIViewController {
    
    var url: String!
    var pokemonId: Int!
    var caughtPokemon: [Int]!

    @IBOutlet var nameLabel: UILabel!
    @IBOutlet var numberLabel: UILabel!
    @IBOutlet var type1Label: UILabel!
    @IBOutlet var type2Label: UILabel!
    @IBOutlet var catchButton: UIButton!
    @IBOutlet var pokemonImage: UIImageView!
    @IBOutlet var pokemonDescription: UITextView!
    
    @IBAction func toggleCatch() {
        if(caughtPokemon.contains(pokemonId)) {
            catchButton.setTitle("Catch", for: .normal)
            caughtPokemon = caughtPokemon.filter { id in return id != pokemonId }
        }
        else {
            caughtPokemon.append(pokemonId)
            UserDefaults.standard.set(caughtPokemon, forKey: "CaughtPokemon")
        }
        updateButton()
    }
    
    func updateButton() {
        if(caughtPokemon.contains(pokemonId)) {
            self.catchButton.setTitle("Release", for: .normal)
        }
        else {
            self.catchButton.setTitle("Catch", for: .normal)
        }
    }
    
    
    func loadDesc() {
            guard let pokemonId = pokemonId, let requestUrl = URL(string: "https://pokeapi.co/api/v2/pokemon-species/\(pokemonId)") else {
                return
            }
            URLSession.shared.dataTask(with: requestUrl) { (data, response, error) in
                guard let data = data else {
                    return
                }

                do {
                    let result = try JSONDecoder().decode(PokemonDescriptionResult.self, from: data)
                    let description = result.flavor_text_entries.first(where: { lan in return lan.language.name == "en" })?.flavor_text ?? ""
                    DispatchQueue.main.async {
                        self.pokemonDescription.text = description.replacingOccurrences(of: "\n", with: " ")
                    }
                }
                catch let error {
                    print(error)
                }
            }.resume()
        }

    func capitalize(text: String) -> String {
        return text.prefix(1).uppercased() + text.dropFirst()
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        self.view.backgroundColor = UIColor.black
        
        caughtPokemon = UserDefaults.standard.array(forKey: "CaughtPokemon") as? [Int] ?? []

        nameLabel.text = ""
        numberLabel.text = ""
        type1Label.text = ""
        type2Label.text = ""

        loadPokemon()
    }

    func loadPokemon() {
        URLSession.shared.dataTask(with: URL(string: url)!) { (data, response, error) in
            guard let data = data else {
                return
            }

            do {
                let result = try JSONDecoder().decode(PokemonResult.self, from: data)
                DispatchQueue.main.async {
                    self.pokemonId = result.id
                    
                    self.navigationItem.title = self.capitalize(text: result.name)
                    self.nameLabel.text = self.capitalize(text: result.name)
                    self.numberLabel.text = String(format: "#%03d", result.id)

                    for typeEntry in result.types {
                        if typeEntry.slot == 1 {
                            let first_label = typeEntry.type.name
                            self.type1Label.text = first_label
                        }
                        else if typeEntry.slot == 2 {
                            let second_label = typeEntry.type.name
                            self.type2Label.text = second_label
                        }
                    }
                    
                    if let url = URL(string: result.sprites.front_default) {
                        self.pokemonImage.imageLoad(imageURL: url)
                    }
                    
                    self.loadDesc()
                    
                    self.updateButton()
                }
            }
            catch let error {
                print(error)
            }
        }.resume()
    }
}

extension UIImageView {
    func imageLoad(imageURL: URL) {
        DispatchQueue.global().async {
            if let data = try? Data(contentsOf: imageURL) {
                if let loadedImage = UIImage(data: data) {
                    DispatchQueue.main.async {
                        self.image = loadedImage
                    }
                }
            }
        }
    }
}
