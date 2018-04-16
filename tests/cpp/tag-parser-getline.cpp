
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

using namespace std;

/****************************************************************
* This substring might vary as per the files to be parsed 
*/
const std::string subString = "@M";

/****************************************************************
* Locate the file to parsered 
*/
const std::string fastqFile = "F_3d.fastq";

/****************************************************************
* Prepare read-only tags map 
*/
map<int, std::string> tagMap = {
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
    {12,   "CTCTTTACTACTAC"}
};


/****************************************************************
* main program starts here  
*/
int main()
{
    /** 
     *  Step 1: create ofstream objects and separate output files 
     */ 
    vector<ofstream> fileList;
    for(unsigned int i=0; i< tagMap.size(); i++)
    {      
        ofstream ofs;
        ofs.open("tag" + to_string(i+1) + ".fastq");
        fileList.push_back(move(ofs));
    }

    /** 
     *  Step 2: create a file-reading object: infile and open fastqFile, if open operation failed return
     */
    std::ifstream infile;
    infile.open(fastqFile); 
    if(!infile.good())  return 1; /* open file error */
	
    /** 
     *  Step 3: read fastqFile line-by-line, basically every four lines will be parsed.
     */
    std::string line1, line2, line3, line4;

    while(true)
    {
        /**
         *  read first lines into line1, if the first line is empty continue reading next line into line1  
        * */
        std::getline(infile, line1);
        if (line1.empty()) break; 

        /*
         *  read the following three lines into line2~4
        * */
        std::getline(infile, line2);
        std::getline(infile, line3);
        std::getline(infile, line4);

        /** Now 4 lines as a group is ready to be parsed...
         *  1. Check if subString(here it is "@M") exists in every first line of each 4 lines (4 lines as a group). 
         *      If exist, then do the parsing. Otherwise, read next 4 lines. 
         *  2. Check tags against every second line of each 4 lines 
         *      If the corresponding tag was found from current line, then write the 4 lines into corresponding output file. 
         */
        if(line1.find(subString) != std::string::npos) 
        {
            for(unsigned int i=0; i<tagMap.size(); i++)
            {       
                if(line2.find(tagMap[i+1]) != std::string::npos)
                {
                    /* once the tag has been found in the first line, write the consecutive 4 lines into corresponding output file */
                    fileList[i] << line1 << endl;
                    fileList[i] << line2 << endl;
                    fileList[i] << line3 << endl;
                    fileList[i] << line4 << endl;

                    /* continue reading next 4 lines, doesn't have to loop the next tags 
                       cause one line cannot contain more than two different tags */
                    break; 
                }
            }  
        }
    }

    cout << "\t*** Parse Completed." << endl;

    return 0;
}
