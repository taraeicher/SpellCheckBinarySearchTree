This program uses a dictionary stored as a binary search tree to perform a spell check. After each run, the dictionary is written to alphaorder.txt. A unix makefile is provided. The following is a sample run:

  Enter a sentence: This is a short statement.
  The word "This" is not in the dictionary.
  Would you like to edit it? (y=yes, N=NO)
  Would you like to add "This" to the dictionary? (y=yes, N=NO) y
  Added "This" ...
  The word "short" is not in the dictionary.
  Would you like to edit it? (y=yes, N=NO) y
  Please enter the edited word: shorter
  Your final sentence is:
  This is a shorter statement.
  The dictionary was saved in the file alphaorder.txt.
