# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

pneumonoultramicroscopicsilicovolcanoconiosis is the longest word in English.

## According to its man page, what does `getrusage` do?

'getrusage' is short for get resource usage. It can be declared with "int getrusage(int WHO, struct rusage *USAGE". According to its description, "getrusage() returns resource usage measures for WHO, which can be one of the following:
RUSAGE_SELF, RUSAGE_CHILDREN, and RUSAGE_THREAD. In speller.c, we see getrusage used with RUSAGE_SELF a lot, which returns "resource usage statistics for the calling process, which is ther sum of resources used by all threads in the process."

## Per that same man page, how many members are in a variable of type `struct rusage`?

There are 16 members in a variable of type 'struct rusage', including 2 other structs and 14 longs.

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

We may pass 'before' and 'after' by reference instead of by value to calculate to save time! When a function passes by value, it makes a copy of that value. When it passes by reference, it follows a pointer to the value.
A bonus of a value being passed by reference is that the variable assigned to it stays the same for the function and anything else which calls it.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

'main' goes about reading words from a file by stitching together words from characters and seeing if they appear in a given list.
How does it accomplish this task?
Let's look at the for loop in speller.c line by line from 68 to 129.
Before the for loop is even executed, we have four variables declared in lines 68 and 69.
Integers index, misspellings, and words, as well as character array (aka string) word.
The integers serve to count, while word serves to store.
index counts the number of characters in a word.
misspellings counts
words counts the number of words.
The for loop is declared with the integer c which is a character cast as an integer as a result of the fgetc function.
fgetc is sicced on file, which is the text inputted as an argument from the user.
The for loop will continue as long as c does not equal EOF (or End of File).
The for loop will increment with fgetc, which simply gets the next character from a file.
There are three top decision making structures inside the for loop.
The first if statement (IF1) checks to see if c is alphabetical or an apostrophe.
IF1's condition is that isalpha(c) returns TRUE or that c is an apostrophe and the index is greater than zero.
IF1 requires that index > 0 if isalpha(c) returns FALSE because an index of 0 in conjunction with an apostrophe simply indicates the beginning of a quote.
Once IF1 confirms c is alphabetical (or an apostrophe), it appends the character to word by setting the indexth element in word to that character.
IF1 then increments index by 1 to indicate there is one more character in word!
Within IF1, we check to see that the number of characters in word is not greater than LENGTH, which is defined in dictionary.h to be 45.
If index > 45, the while loop insures that fgetc moves c through the characters in file until it encounters EOF or something that is not alphabetical.
If index > 45, the while loop eventually resets the index to 0.
The second decision-making structure, ELIF1, "[Ignores] words with numbers...."
isdigit checks to see if c is a numeric digit.
Within ELIF1 we find the same while loop as in IF1, which consumes the remainder of the string and resets the index counter.
ELIF2 explores the space where c is not alphabetical or an apostrophe or a number, but index > 0.
That being the case, "We must have found a whole word".
First, the word is terminated by setting the indexth character in word to NULL or \0.
The word counter is then incremented by 1 (word++).
The word's spelling is checked with the check function.
The performance of the function is measured with getrusage, and a boolean misspelled indicates if the word is indeed misspelled.
The time benchmark is updated using the metric from getrusage.
If the word is misspelled, it is printed as per a nested if statement in ELIF2, and the misspellings integer is increment.
Subsequently, the program prepares for the next word by resetting the index to zero.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fgetc() allows us to be more flexible with the types of files we read as it reads character by character. Punctuation is seen as part of a string in C, so periods, quotation marks, hyphens, commas, and more will be included in the strings extracted as part of words.
fgetc() is more precise than fscanf() and allows us to check each character and test there sequence to see if we truly have a word and to know when to end it.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

check refers to word and load refers to dictionary. These values need be fixed values, or constants!