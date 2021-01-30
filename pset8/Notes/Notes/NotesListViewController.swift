import UIKit

class NotesListViewController: UITableViewController {
    var notes: [Note] = []
    
    @IBAction func createNote() {
        let _ = NoteManager.shared.create()
        reload()
    }
    
    func reload() {
        notes = NoteManager.shared.getNotes()
        tableView.reloadData()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        reload()
    }
    
    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return notes.count
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
            let cell = tableView.dequeueReusableCell(withIdentifier: "NoteCell", for: indexPath)
            cell.textLabel?.text = notes[indexPath.row].content
            cell.textLabel?.tag = indexPath.row

            cell.textLabel?.isUserInteractionEnabled = true
            let swipeLeft = UISwipeGestureRecognizer(target: self, action: #selector(self.labelSwipedLeft(sender:)))
            swipeLeft.direction = .left
            cell.textLabel?.addGestureRecognizer(swipeLeft)

            return cell
        }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "NoteSegue",
                let destination = segue.destination as? NoteViewController,
                let index = tableView.indexPathForSelectedRow?.row {
            destination.note = notes[index]
        }
    }
    
    @objc func labelSwipedLeft(sender: UISwipeGestureRecognizer) {
            deleteNote(noteRow: sender.view!.tag)
        }

    func deleteNote(noteRow: Int) {
        let ac = UIAlertController(title: "Are you sure you want to delete this note?", message: notes[noteRow].content, preferredStyle: .alert)

        let yes: UIAlertAction = UIAlertAction(title: "Yes", style: .default, handler: {
            (action: UIAlertAction!) -> Void in
            NoteManager.shared.delete(note: self.notes[noteRow])
            self.reload()
        })
        let no: UIAlertAction = UIAlertAction(title: "No", style: .cancel)

        ac.addAction(yes)
        ac.addAction(no)

        present(ac, animated: true)
    }
}
