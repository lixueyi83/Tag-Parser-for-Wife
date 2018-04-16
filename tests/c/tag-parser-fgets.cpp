
/********************************************************************************************
*   How to run the progra
*   0. Make sure the build tool is executable: $ chmod +x makecpp
*   1. Build the executable binary in command line: $ makecpp tags_parser.cpp
*   2. Run the executable: $ ./tags_parser
********************************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <stdio.h>
#include <string.h>
#include <stdio.h>

using namespace std;

const int MAX_LINE = 500;

/****************************************************************
* This machine_id might vary as per the files to be parsed 
*/
const char* machine_id = "@M";

/****************************************************************
* Locate the file to parsered 
*/
const char* fastqFile = "F_3d.fastq";

/****************************************************************
* Prepare read-only tags map 
*/

typedef struct 
{
    int i;
    const char* tag;
}TAG_MAP;

TAG_MAP tagMap[12] = {
    {1,    "CTCTTGATGATGAT"},
    {2,    "CTCTTAGTAGTAGT"},
    {3,    "CTCTTTGATGATGA"},
    {4,    "CTCTTGTAGTAGTA"},
    {5,    "CTCTTATGATGATG"},
    {6,    "CTCTTTAGTAGTAG"},
    {7,    "CTCTTCATCATCAT"},
    {8,    "CTCTTACTACTACT"},
    {9,    "CTCTTTCATCATCA"},
    {10,   "CTCTTCTACTACTA"},
    {11,   "CTCTTATCATCATC"},
    {12,   "CTCTTTACTACTAC"},
};


/****************************************************************
* main program starts here  
*/
int main()
{
    /** 
     *  Step 1: create ofstream objects and separate output files 
     */ 
    vector<FILE*> outfiles;
    for(unsigned int i=0; i< sizeof(tagMap)/sizeof(TAG_MAP); i++)
    {
        const char *fileList[12] = { "tag1.fastq", "tag2.fastq", "tag3.fastq", "tag4.fastq", "tag5.fastq", "tag6.fastq", 
                                     "tag7.fastq", "tag8.fastq", "tag9.fastq", "tag10.fastq", "tag11.fastq", "tag12.fastq" };

        FILE* pFile = fopen(fileList[i], "w");
        outfiles.push_back(move(pFile));
    }

    /** 
     *  Step 2: create a file-reading object: infile and open fastqFile, if open operation failed return
     */
    FILE* infile = fopen(fastqFile, "r");
    if(infile == NULL) 
    {
        cout << "\t*** Error opening files " << endl; 
        return 1; /* open file error */
    }

    /** 
     *  Step 3: read fastqFile line-by-line, basically every four lines will be parsed.
     */
    char line1[MAX_LINE];
    char line2[MAX_LINE];
    char line3[MAX_LINE];
    char line4[MAX_LINE];
  
    while(true)
    {
        /**
         *  read 4 lines into line1~4, if hits EOF break loop.  
        * */
        if(fgets(line1, MAX_LINE, infile) == NULL) break;  
        if(fgets(line2, MAX_LINE, infile) == NULL) break;
        if(fgets(line3, MAX_LINE, infile) == NULL) break; 
        if(fgets(line4, MAX_LINE, infile) == NULL) break; 

        /** Now 4 lines as a group is ready to be parsed...
         *  1. Check if machine_id(here it is "@M") exists in every first line of each 4 lines (4 lines as a group). 
         *      If exist, then do the parsing. Otherwise, read next 4 lines. 
         *  2. Check tags against every second line of each 4 lines 
         *      If the corresponding tag was found from current line, then write the 4 lines into corresponding output file. 
         */ 
        if(strstr(line1, machine_id) != NULL)
        {
            for(unsigned int i=0; i< sizeof(tagMap)/sizeof(TAG_MAP); i++)
            {
                if(strstr(line2, tagMap[i].tag) != NULL)
                {
                    /* once the tag has been found in the first line, write the consecutive 4 lines into corresponding output file */
                    fputs(line1, outfiles[i]);
                    fputs(line2, outfiles[i]);
                    fputs(line3, outfiles[i]);
                    fputs(line4, outfiles[i]);

                    /* continue reading next 4 lines, doesn't have to loop the next tags 
                       cause one line cannot contain more than two different tags */
                    break; 
                }
            }  
        }
    }

    cout << "\t*** Parse Completed." << endl;

    fclose(infile);

    return 0;
}
