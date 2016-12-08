
#include <iostream> // library that contain basic input/output functions
#include <fstream>  // library that contains file input/output functions

using namespace std;


int array_size = 1024*100000; // size of our input file
char * array = new char[array_size];
long int rev=0;
long int nextRev  = 9;
long int position = 0; //this will be used incrementally to fill characters in the array
bool endDoc = false;
bool endFlag= false;
char buffer[2000];
long int buffer_count=0;
void countString(char arr[],int length);

ofstream csv;

void newRevision(void);
long int pos(char arr[] , int length);
void save(long int x , long int y , int extra);
void addToExcel(void);

int main()
{

	ifstream fin("svnfull.txt"); //opening an input stream for file

	/*checking whether file could be opened or not. If file does not exist or don't have read permissions, file
     stream could not be opened.*/

  if(fin.is_open())
	{

    cout << "File Opened successfully!!!. Reading data from file into array" << endl;

    //this loop run until end of file (eof) does not occur

		while(!fin.eof() && position < array_size)
		{
			fin.get(array[position]); //reading one character from file to array
			position++;
		}


        csv.open("full_Record.csv");



		char author[7]  = {'A','u','t','h','o','r',':'};
		char date[5]    = {'D','a','t','e',':'};
		char message[8] = {'M','e','s','s','a','g','e',':'};
		char modified[10] = {'M','o','d','i','f','i','e','d','\0',':'};
		char added[5] = {'A','d','d','e','d'};

        csv << "Revision," << "Author," << "Date and Time," << "Modified," << "Added"<<endl;
		    while(!endDoc)
            {
                newRevision();
                save(rev, pos(author,7), 7);
                save(pos(author,7),pos(date,5),5);
                save(pos(date,5),pos(message,8),8);
                countString(modified,8);
                countString(added,5);
                addToExcel();
            }
            csv.close();
	}
	else
        {
            cout << "File could not be opened or maybe not present in the same folder" << endl;
        }


	return 0;
}

void newRevision(void)
{
    if(endFlag==true){
        endDoc=true;
    }
  rev = nextRev;

    for(int i=rev; i <=position; i++)
    {
            if(array[i]=='R'&& array[i+1]=='e' && array[i+2]=='v' && array[i+3]=='i' &&
               array[i+4]=='s' && array[i+5]=='i' && array[i+6]=='o'
               && array[i+7]=='n' && array[i+8]==':')
               {

                nextRev=i+9;
                endDoc = false;
                break;

               }

               else
                { nextRev=rev+5000;
                    endFlag=true;
                }
    }
}

long int pos(char arr[] , int length)
{

   int counts=0;
    for(int i=rev; i < nextRev ; i++)
    {
        for(int j=0; j<length ; j++)
        {
            if(array[i+j] == arr[j])
            {
                counts++;
            }

        }
        if(counts == length)
            {
            return (i+length);
            }
            counts=0; // THIS LINE WAS NOT ADDED WHICH TOOK ME 2 HRS TO CORRECT :D

    }
}

void save(long int x , long int y , int extra )
{
  for(int i=x; i<(y - extra - 1) ; i++)
  {
          buffer[buffer_count] = array[i];
          buffer_count++;
  }
  buffer[buffer_count] = ',';
  buffer_count++;

}
void addToExcel(void)
{

    for(int i=0; i<buffer_count; i++)
    {
        cout << buffer[i];
        csv << buffer[i];

    }
   cout << endl;
   csv << endl;

    buffer_count=0;
}

void countString(char arr1[],int lengths)
{   int counts=0;
    int occurance=0;
    for(int i=rev;i<nextRev;i++)
    {
        for(int j=0; j< lengths ; j++)
            {
           if( array[i+j] == arr1[j]) counts++;

        }
        if(counts==lengths) occurance++;
        counts=0;
    }
     if(occurance==0)
          {
            buffer[buffer_count]='0';
             buffer_count++;
          }
        else
            {
        int lastBit=0;
        char sequence[5];
        int digits=0;

         while(occurance>0)
         {
            lastBit=occurance%10;
             sequence[digits]=lastBit+'0';
             digits++;
             occurance /= 10;
          }
          for(int n=digits-1 ; n>=0; n--)
            {
               buffer[buffer_count] = sequence[n];
               buffer_count++;
            }
        }

     buffer[buffer_count]=',';
     buffer_count++;

}
