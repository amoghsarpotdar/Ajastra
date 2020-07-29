# Ajastra
Chess engine built using c++


Local Build :
CMake
If you are using Visual Studio on Windows and want to know more about CMake Integration - https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=vs-2019

Unit Testing :
Boost.Test is used to unit test the code. You will have to build the BOOST framework on your local platform. More information can be found here - 'http://goodliffe.blogspot.com/2008/05/cross-compiling-boost.html'


Board representation



________________________________________       _______________________________         ______________________________
|0  |1  |2  |3  |4  |5  |6  |7  |8  |9  |      |* |a |b |c |d |e |f |g |h |* |         |* |a |b |c |d |e |f |g |h |* |
-----------------------------------------      -------------------------------         -------------------------------
|10 |11 |12 |13 |14 |15 |16 |17 |18 |19 |      |1 |0 |1 |2 |3 |4 |5 |6 |7 |* |         |8 |0 |0 |0 |0 |0 |0 |0 |0 |* |
----------------------------------------      -------------------------------         -------------------------------
|20 |21 |22 |23 |24 |25 |26 |27 |28 |29 |      |2 |8 |9 |10|11|12|13|14|15|* |         |7 |0 |0 |0 |0 |0 |0 |0 |0 |* |
-----------------------------------------      -------------------------------         -------------------------------
|30 |31 |32 |33 |34 |35 |36 |37 |38 |39 |      |3 |16|17|18|19|20|21|22|23|* |         |6 |0 |0 |0 |0 |0 |0 |0 |0 |* |
-----------------------------------------      -------------------------------         -------------------------------
|40 |42 |43 |44 |45 |46 |47 |48 |49 |50 |      |4 |24|25|26|27|28|29|30|31|* |         |5 |0 |0 |0 |0 |0 |0 |0 |0 |* |
-----------------------------------------      -------------------------------         -------------------------------
|50 |51 |52 |53 |54 |55 |56 |57 |58 |59 |      |5 |32|33|34|35|36|37|38|39|* |         |4 |0 |0 |0 |0 |0 |0 |0 |0 |* |
-----------------------------------------      -------------------------------         -------------------------------
|60 |61 |62 |63 |64 |65 |66 |67 |68 |69 |      |6 |40|41|42|43|44|45|46|47|* |         |3 |0 |0 |0 |0 |0 |0 |0 |0 |* |
-----------------------------------------      -------------------------------         -------------------------------
|70 |71 |72 |73 |74 |75 |76 |77 |78 |79 |      |7 |48|49|50|51|52|53|54|55|* |         |2 |0 |0 |0 |0 |0 |0 |0 |0 |* |
-----------------------------------------      -------------------------------         -------------------------------
|80 |81 |82 |83 |84 |85 |86 |87 |88 |89 |      |8 |56|57|58|59|60|61|62|63|* |         |1 |0 |0 |0 |0 |0 |0 |0 |0 |* |
-----------------------------------------      -------------------------------         -------------------------------
|90 |91 |92 |93 |94 |95 |96 |97 |98 |99 |                                                                             
-----------------------------------------                                                                             
|100|101|102|103|104|105|106|107|108|109|                                                                             
-----------------------------------------                                                                             
|110|111|112|113|114|115|116|117|118|119|
-----------------------------------------













64 bit number representation



-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
|63|62|61|60|59|58|57|56|55|54|53|52|51|50|49|48|47|46|45|44|43|42|41|40|39|38|37|36|35|34|33|32|31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10|09|08|07|06|05|04|03|02|01|00|           <<--Bit Number
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
|H8|G8|F8|E8|D8|C8|B8|A8|H7|G7|F7|E7|D7|C7|B7|A7|H6|G6|F6|E6|D6|C6|B6|A6|H5|G5|F5|E5|D5|C5|B5|A5|H4|G4|F4|E4|D4|C4|B4|A4|H3|G3|F3|E3|D3|C3|B3|A3|H2|G2|F2|E2|D2|C2|B2|A2|H1|G1|F1|E1|D1|C1|B1|A1|           <<--Square on board
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
|0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |           <<--Piece indicator
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Examples :
1. Piece exists on A1 and H1
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
|63|62|61|60|59|58|57|56|55|54|53|52|51|50|49|48|47|46|45|44|43|42|41|40|39|38|37|36|35|34|33|32|31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10|09|08|07|06|05|04|03|02|01|00|           <<--Bit Number
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
|H8|G8|F8|E8|D8|C8|B8|A8|H7|G7|F7|E7|D7|C7|B7|A7|H6|G6|F6|E6|D6|C6|B6|A6|H5|G5|F5|E5|D5|C5|B5|A5|H4|G4|F4|E4|D4|C4|B4|A4|H3|G3|F3|E3|D3|C3|B3|A3|H2|G2|F2|E2|D2|C2|B2|A2|H1|G1|F1|E1|D1|C1|B1|A1|           <<--Square on board
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
|0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |1 |0 |0 |0 |0 |0 |0 |1 |           <<--Piece indicator
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2. Piece exists on A1 and H8
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
|63|62|61|60|59|58|57|56|55|54|53|52|51|50|49|48|47|46|45|44|43|42|41|40|39|38|37|36|35|34|33|32|31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10|09|08|07|06|05|04|03|02|01|00|           <<--Bit Number
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
|H8|G8|F8|E8|D8|C8|B8|A8|H7|G7|F7|E7|D7|C7|B7|A7|H6|G6|F6|E6|D6|C6|B6|A6|H5|G5|F5|E5|D5|C5|B5|A5|H4|G4|F4|E4|D4|C4|B4|A4|H3|G3|F3|E3|D3|C3|B3|A3|H2|G2|F2|E2|D2|C2|B2|A2|H1|G1|F1|E1|D1|C1|B1|A1|           <<--Square on board
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
|1 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |0 |1 |0 |0 |0 |0 |0 |0 |1 |           <<--Piece indicator
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


Setting the bits using shift operators : 










Important c++ concepts you will have to know to be able to understand/modify this code:
1. Bitwise operators
	1a. bitwise AND : Takes two numbers as operands and does AND on every bit of two numbers. The result of AND is 1 only if both bits are 1.
	1b. bitwise OR : Takes two numbers as operands and does OR on every bit of two numbers. The result of OR is 1 if any of the two bits is 1.
	1c. bitwise XOR : Takes two numbers as operands and does XOR on every bit of two numbers. The result XOR is 1 if the two bits are different.
	1d. left shift : Takes two numbers, left shifts the bits of the first operand, the second operand decides the number of places to shift.
	1e. right shift : Takes two numbers, right shifts the bits of the first operands, second operand decides number of places to shift.
	1f. bitwise NOT : Takes one number and inverts all bits of it.
2. Why bitwise operations and not standard c++ operators?
-> https://softwareengineering.stackexchange.com/questions/13798/what-are-the-advantages-of-using-bitwise-operations#:~:text=This%20means%20making%20extensive%20use,into%20the%20payload%20being%20transmitted.&text=Basically%2C%20you%20use%20them%20due,usually%20faster%20than%20arithmetic%20operations.
3. Whats 1ULL?
-> Unsigned long long
Read more about this at - https://stackoverflow.com/questions/17795722/what-is-the-meaning-of-1ullin-c-programming-language
and at https://stackoverflow.com/questions/17287680/literal-types-0x1ull-vs-0x1llu/17287767#17287767
and at https://stackoverflow.com/questions/17287957/is-long-unsigned-as-valid-as-unsigned-long-in-c
4. How are position keys generated?
-> The C library rand() is being used to generate random number.
A 64bit value will be represented in memory as below -
<-4-><------15-----> <------15-----> <------15-----> <-----15------>
0000 000000000000000 000000000000000 000000000000000 000000000000000
The rnd function will generate 15 bit value, which means only the 15 bits will be occupied to reflect the value.
<-4-><------15-----> <------15-----> <------15-----> <-----15------>
0000 000000000000000 000000000000000 000000000000000 111111111111111
The RAND_64 function in init.h is using left shift operations to generate the random number and
left shift it into the 64bit at each step. Thus after four steps it will occupy 60 bits as shown beow
<-4-><------15-----> <------15-----> <------15-----> <-----15------>
0000 111111111111111 111111111111111 111111111111111 111111111111111
The final step will deal with remaining bits.


What needs to change in this implementation:
1. This code is based on original work done in C language. The migration to C++ is
not complete and you will notice elements from C hanging around, which need to be
migrated to C++.
2. Bitboard implementation is not 100%. Only pawns are being represented using binary
arrays. For a faster and precise operation bitboard implementation needs to be perfected.


FEN Notation: More information is available here - https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
->Example string : rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
Here:
1. Small letters indicate black pieces.
2. Capital letters indicate white pieces.
3. The /8/8/8/8 indicate the vacant squares.
4. 'w' indicates side to move.
5. KQkq indicates castling rights for each side.
6. The 0 indicates halfmove clock : Number of half moves since the last capture of pawn advance (fifty-move rule).
7. Final digit (1 in this case) indicate number of full moves, starts with 1 and is incremented after Black's move.
8. All piece placement is from White's perspective.
->Example string after White's e4 : rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1
Notice the third '/8' being replaced by 4P3 which indicates a white pawn on 4th file pawn (index starting with 0) moving to third row (index starting with 0).



