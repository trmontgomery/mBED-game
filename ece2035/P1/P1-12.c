/*            Diamond Sort


February 17 2018    	         Tiffany Montgomery

This program sorts a diamond array of disks of varying hues and
diameters. */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   int	Array[169];
   int	NumVals;
   int  Load_Mem(char *, int *);
   void	Print_Array(int *);

   if (argc != 2) {
     printf("usage: %s valuefile\n", argv[0]);
     exit(1);
   }
   NumVals = Load_Mem(*++argv, Array);
   if (NumVals != 85) {
      printf("not enough values in %s\n", argv[0]);
      exit(1);
   }

    /* my code starts here */
    
    int j, m, n, length, temp, ndx, ndx2, currd, currh, change, jstart, jend, start;
    currd = 1;
    currh = 1;
    change = 2;
    

    
    while(currd!= 0 && currh !=0){
        
        currh = 0;
        currd = 0;
        
    ////////////////////////////////DIAMETER SORT//////////////////////////
    //sort first half of diameter
        length = 3;
        jstart = 1;
        jend = 7;

    
        for (j = jstart; j < jend; j++){
            start = 6-j;
            for (m = start; m < (start)+(length-1); m++){
                for(n = start; n < (start)+(length-1); n++){
                    if (change % 2 == 0){
                        ndx = n * 13 + j;
                        ndx2 = (n+1) * 13 + j;
                    } else{
                        ndx = j * 13 + n;
                        ndx = j * 13 + (n+1);
                    }
                    if (Array[ndx]/64 > Array[ndx2]/64){
                        temp = Array[ndx];
                        Array[ndx] = Array[ndx2];
                        Array[ndx2] = temp;
                        if (change % 2 == 0){
                            currd++;
                        } else {
                            currh++;
                        }
                    }
                }
            }
            length = length + 2;
            printf("Loop1 executed. Change: %d, Currd: %d, Currh: %d\n", change, currd, currh);
        }
 
        //sort second half of diameter
        
        jstart = 7;
        jend = 12;
        length = 11;
        for (j = jstart; j < jend; j++){
            start = j-6;
            for (m = start; m < (start)+(length-1); m++){
                for(n = start; n < (start)+(length-1); n++){
                    if (change % 2 == 0){
                        ndx = n * 13 + j;
                        ndx2 = (n+1) * 13 + j;
                    } else {
                        ndx = j * 13 + n;
                        ndx2 = j * 13 + (n+1);
                    }
               
                    if (Array[ndx]/64 > Array[ndx2]/64){
                        temp = Array[ndx];
                        Array[ndx] = Array[ndx2];
                        Array[ndx2] = temp;
                        if (change % 2 == 0){
                            currd++;
                        } else {
                            currh++;
                        }
                    }
                }
                printf("Inner Loop2 executed. Change: %d. Currd: %d, Currh: %d\n", change, currd, currh);
            }

            length = length - 2;
            printf("Loop2 executed. Change: %d. Currd: %d, Currh: %d\n", change, currd, currh);
        }
        
        change++;
        
    }

    /*/////////////////////////////HUE SORT//////////////////////////////////
    
    ////UPPER HALF///
    length = 3;
    for (i = 1; i < 7; i++){
        for (m = 6-i; m < (6-i)+(length-1); m++){
            for(n = 6-i; n < (6-i)+(length-1); n++){
                ndx = i * 13 + n;
                ndx2 = i * 13 + (n+1);
                if (Array[ndx]%64 > Array[ndx2]%64){
                    temp = Array[ndx];
                    Array[ndx] = Array[ndx2];
                    Array[ndx2] = temp;
                    currh++;
                }
            }
        }
        length = length + 2;
    }
    
    //LOWER HALF//////
    length = 11;
    for (j = 7; j < 12; j++){
        for (m = j-6; m < (j-6)+(length-1); m++){
            for(n = j-6; n < (j-6)+(length-1); n++){
                ndx = j * 13 + n;
                ndx2 = j * 13 + (n+1);
                if (Array[ndx]%64 > Array[ndx2]%64){
                    temp = Array[ndx];
                    Array[ndx] = Array[ndx2];
                    Array[ndx2] = temp;
                    currh++;
                }
            }
        }
        length = length - 2;
    }
        
        
    }
    
    //my code ends here */

   Print_Array(Array);
   exit(0);
}

/* This routine initializes a 13 x 13 array with zeros. Then it loads
85 memory elements from the input file. The values are loaded in
address: value tuples. The first value is loaded into position 6. All
other values are positioned relative to the address of the first word.
The number of loaded values are returned. */

int Load_Mem(char *InputFileName, int Array[]) {
   int	N, Addr, Value, Index, NumVals;
   int	Base = -1;
   FILE	*FP;

   for (N=0; N < 169; N++)
     Array[N] = -1;
   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
      printf("%s could not be opened; check the filename\n", InputFileName);
      return 0;
   } else {
      for (N=0; N < 85; N++) {
         NumVals = fscanf(FP, "%d: %d", &Addr, &Value); //Why the addressing? Why not just pass Addr or Value?
         if (NumVals != 2)
            break;
         else
            //printf("LoadMem Output1: %d: %d\n", Addr, Value);
            if (Base == -1)
               Base = Addr - 24;   //What is this doing?
            Index = (Addr - Base) / 4; //What?
            Array[Index] = Value;
            //printf("LoadMem Output2: %d: %d\n", Addr, Value);
      }
      fclose(FP);
      return N;
   }
}

/* This routine prints a diamond. The hue and diameter are unpacked before printing.
Empty array cells are printed as blanks. */

void Print_Array(int Array[]) {
   int	N, Value, Diameter, Hue;

   for (N=0; N < 169; N++) {
      Value = Array[N];
      if (Value == -1)
         printf("      ");
      else {
         Diameter = Value / 64;
         Hue = Value % 64;
         printf("%02d:%02d ", Diameter, Hue);
      }
      if ((N % 13) == 12)
         printf("\n");
   }
}