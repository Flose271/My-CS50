My CS50 project is a python program that lets you play Cluedo with perfect deduction skills, 
by keeping track of which cards people do, don’t, or could have in their hands. 
Once we know a card is not in anyone’s hands, 
we can deduce that it is in the murderer’s hand and we have won the game.  

There are two lists of lists that keep track of cards. 
The first keeps track of which cards people don’t have in their hands. 
This is ultimately what we use to figure out what the murderer’s hand is. 
The second keeps track of sets of cards that people might have. 
For example, if someone responds to [‘White’, ‘Kitchen’, ‘Axe’] then we assign that set to them.  

If we later find out they don’t have one of the cards in that set, we reduce the set down. 
For example, if we later find out they don’t have ‘White’ or ‘Kitchen’, we know that player 
has ‘Axe’ and [‘White’, ‘Kitchen’, ‘Axe’] changes to [‘Axe’]. 
Then ‘Axe’ is added to everyone else’s list of cards they don’t have.

This process continues until all the murderer's cards are known and we win!

My accompanying video:
https://youtu.be/rzXpov_Nwe0