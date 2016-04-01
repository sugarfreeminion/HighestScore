/*************************************************************************
 * Author:          sugarfreeoh
 * Date:            7 March 2016
 * Description:     Each input line includes a test case with a table.
 *                  Table rows are separated by pipes. All table rows
 *                  contain scores for each category. Determine the 
 *                  highest score for each category.
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const unsigned int ROWSIZE=10;
const unsigned int COLSIZE=20;

int MaxScore(int scores[ROWSIZE][COLSIZE], int colIndex, unsigned int filledRow);

int main(int argc, char *argv[])
{
    ifstream inputFile;

    inputFile.open(argv[1]);

    if(inputFile.is_open())
    {
        string line;

        while(getline(inputFile,line))
        {
            int scores[ROWSIZE][COLSIZE];

            stringstream lineStream;

            string row;
            
            lineStream << line;

            unsigned int rowIndex = 0;
            unsigned int colIndex = 0;

            unsigned int filledRow = 0;
            unsigned int filledCol = 0;

            while(rowIndex < ROWSIZE)
            {
                while(colIndex < COLSIZE)
                {
                    scores[rowIndex][colIndex] = -1001;

                    ++colIndex;
                }

                ++rowIndex;
            }

            rowIndex = 0;
            colIndex = 0;

            while(getline(lineStream,row,'|'))
            {
                filledCol = 0;
                colIndex = 0;
                unsigned int index = 0;
                string val = "";

                stringstream ss;

                if(row[0] == ' ')
                    row = row.substr(1);

                if(row[row.size()-1] == ' ')
                    row = row.substr(0,row.size()-1);

                //cout << "INPUT: " << row << endl;
                
                while(index < row.size())
                {
                    if((row[index] != ' ') && index != row.size()-1)
                    {
                        val = val + row[index];
                    }
                    else if(index == row.size()-1)
                    {
                        val = val + row[index];

                        ss << val;
                        ss >> scores[rowIndex][colIndex];

                        ss.str("");
                        ss.clear();

                        //cout << "At [" << rowIndex << "][" << colIndex << "]" << scores[rowIndex][colIndex] << endl;

                        ++colIndex;
                        ++filledCol;
                    }
                    else
                    {
                        ss << val;
                        ss >> scores[rowIndex][colIndex];

                        //cout << "At [" << rowIndex << "][" << colIndex << "]" << scores[rowIndex][colIndex] << endl;

                        ++colIndex;
                        ++filledCol;

                        ss.str("");
                        ss.clear();
                        val = "";
                    }
                    ++index;
                }

                ++rowIndex;
                ++filledRow;
            }

            unsigned int temp = 0;    
            
            int maxScore;

            while(temp < filledCol)
            {
                maxScore = MaxScore(scores,temp,filledRow);
                if(maxScore != -1001)
                {
                    if(temp < filledCol-1)
                        cout << maxScore << " ";
                    else if(temp == filledCol-1)
                        cout << maxScore << endl;
                        
                }
                ++temp;
            }
            
        }

        inputFile.close();
    }
    else
    {
        cout << "Error opening input file" << endl;
    }

    return 0;
}

int MaxScore(int scores[ROWSIZE][COLSIZE], int colIndex,unsigned int filledRow)
{
    unsigned int rowIndex = 0;

    int maxScore = -1001;

    while(rowIndex < filledRow)
    {
        if(scores[rowIndex][colIndex] > maxScore)
            maxScore = scores[rowIndex][colIndex];

        ++rowIndex;
    }

    return maxScore;
}
