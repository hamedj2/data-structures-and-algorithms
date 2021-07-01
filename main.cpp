#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include "rapidcsv.h"
#include <bits/stdc++.h>
using namespace std;

struct sampleData {
    double X;
    double Y;
    int OBJECTID;
    int ID;
    string NAME;
    string ADDRESS;
    string CITY;
    string STATE;
    int ZIP;
    string ZIP4;
    string TELEPHONE;
    string TYPE;
    string STATUS;
    int POPULATION;
    string COUNTY;
    int COUNTYFIPS;
    string COUNTRY;
    double LATITUDE;
    double LONGITUDE;
    int NAICS_CODE;
    string NAICS_DESC;
    string SOURCE;
    string SOURCEDATE;
    string VAL_METHOD;
    string VAL_DATE;
    string WEBSITE;
    string ST_SUBTYPE;
};

vector<sampleData> readCSV() {
    vector<sampleData> samples;
    vector<string> results;
    sampleData sample;
    rapidcsv::Document doc("/data/Child_Care_Centers.csv");
    int index = 0;
    while (index <= doc.GetRowCount() - 1) {
        results = doc.GetRow<string>(index);
        sampleData sample;
        sample.X = ::stof(results[0].c_str());
        sample.Y = ::stof(results[1].c_str());
        sample.OBJECTID = ::stoi(results[2]);
        sample.ID = ::stoi(results[3].c_str());
        sample.NAME = results[4].c_str();
        sample.ADDRESS = results[5].c_str();
        sample.CITY = results[6].c_str();
        sample.STATE = results[7].c_str();
        sample.ZIP = ::stoi(results[8].c_str());
        sample.ZIP4 = results[9].c_str();
        sample.TELEPHONE = results[10].c_str();
        sample.TYPE = results[11].c_str();
        sample.STATUS = results[12].c_str();
        sample.POPULATION = ::stoi(results[13]);
        sample.COUNTY = results[14].c_str();
        sample.COUNTYFIPS = ::stoi(results[15].c_str());
        sample.COUNTRY = results[16].c_str();
        sample.LATITUDE = ::stof(results[17].c_str());
        sample.LONGITUDE = ::stof(results[18].c_str());
        sample.NAICS_CODE = ::stoi(results[19].c_str());
        sample.NAICS_DESC = results[20].c_str();
        sample.SOURCE = results[21].c_str();
        sample.SOURCEDATE = results[22].c_str();
        sample.VAL_METHOD = results[23].c_str();
        sample.VAL_DATE = results[24].c_str();
        sample.WEBSITE = results[25].c_str();
        sample.ST_SUBTYPE = results[26].c_str();
        samples.push_back(sample);
        index ++;
    }
    return samples;
}

void writeCSV(string fileName, vector<sampleData> samples) {
    std::string file_path(fileName);
    std::ofstream out_s(file_path, std::ofstream::app);
    if (out_s) {
	out_s <<"X"<<','<<"Y"<<','<<"OBJECTID"<<','<<"ID"<<','<<"NAME"<<','<<"ADDRESS"<<','<<"CITY"<<','<<"STATE"
		<<','<<"ZIP"<<','<<"ZIP4"<<','<<"TELEPHONE"<<','<<"TYPE"<<','<<"STATUS"<<','<<"POPULATION"<<','
		<<"COUNTY"<<','<<"COUNTYFIPS"<<','<<"COUNTRY"<<','<<"LATITUDE"<<','<<"LONGITUDE"<<','<<"NAICS_CODE"
		<<','<<"NAICS_DESC"<<','<<"SOURCE"<<','<<"SOURCEDATE"<<','<<"VAL_METHOD"<<','<<"VAL_DATE"<<','<<"WEBSITE"<<','<<"ST_SUBTYPE"<<endl;
        for (const sampleData &record : samples) {
            out_s << record.X << ',' << record.Y << ',' << record.OBJECTID << ',' << record.ID << ',' << record.NAME
                  << ',' << record.ADDRESS << ',' << record.CITY << ',' << record.STATE << ','
                  << record.ZIP << ',' << record.ZIP4 << ',' << record.TELEPHONE << ',' << record.TYPE << ','
                  << record.STATUS << ',' << record.POPULATION << ',' << record.COUNTY << ',' << record.COUNTYFIPS
                  << ',' << record.COUNTRY << ',' << record.LATITUDE << ',' << record.LONGITUDE << ','
                  << record.NAICS_CODE << ',' << record.NAICS_DESC << ',' << record.SOURCE << ',' << record.SOURCEDATE
                  << ',' << record.VAL_METHOD << ',' << record.VAL_DATE << ',' << record.WEBSITE << ','
                  << record.ST_SUBTYPE
                  << endl;
        }
    }
    out_s.close();
}

void insertion_sort(vector<sampleData> &data, int nElements) {
    int x, y;
    sampleData key;
    for (x = 1; x < nElements; x++) {
        key = data[x];
        y = x - 1;
        while (y >= 0 && data[y].NAME >= key.NAME) {
            data[y + 1] = data[y];
            y = y - 1;
        }
        data[y + 1] = key;
    }
}

vector<sampleData> mergeSort(vector<sampleData> &avector) {
    if (avector.size() > 1) {
        int mid = avector.size() / 2;
        vector<sampleData> lefthalf(avector.begin(), avector.begin() + mid);
        vector<sampleData> righthalf(avector.begin() + mid, avector.begin() + avector.size());

        lefthalf = mergeSort(lefthalf);
        righthalf = mergeSort(righthalf);

        unsigned i = 0;
        unsigned j = 0;
        unsigned k = 0;
        while (i < lefthalf.size() && j < righthalf.size()) {
            if (lefthalf[i].NAME < righthalf[j].NAME) {
                avector[k] = lefthalf[i];
                i++;
            } else {
                avector[k] = righthalf[j];
                j++;
            }
            k++;
        }

        while (i < lefthalf.size()) {
            avector[k] = lefthalf[i];
            i++;
            k++;
        }

        while (j < righthalf.size()) {
            avector[k] = righthalf[j];
            j++;
            k++;
        }

    }
    return avector;
}

int partition(vector<sampleData> &array, int low, int high) {
    sampleData pivot = array[high];
  int i = (low - 1);
  for (int j = low; j < high; j++) {
    if (array[j].NAME <= pivot.NAME) {
      i++;
      swap(array[i], array[j]);
    }
  }
  swap(array[i + 1], array[high]);
  return (i + 1);
}
void quickSort(vector<sampleData> &array, int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, high);
  }
}

void quickSort_hybrid(vector<sampleData> &array, int low, int high)
{
    int cutoff=20;
    if(low+cutoff < high){
        int pi = partition(array, low, high);
        quickSort_hybrid(array, low, pi - 1);
        quickSort_hybrid(array, pi + 1, high);
    }
    else
        insertion_sort(array, high-low);
}

void heapify(vector<sampleData> &arr, int n, int i) {
  int max = i;
  int leftChild = 2 * i + 1;
  int rightChild = 2 * i + 2;
  if (leftChild < n && arr[leftChild].NAME > arr[max].NAME)
    max = leftChild;
 if (rightChild < n && arr[rightChild].NAME > arr[max].NAME)
    max = rightChild;
  if (max != i) {
    swap(arr[i], arr[max]);
    heapify(arr, n, max);
  }
}
void heapSort(vector<sampleData> &arr, int n) {
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);
  for (int i = n - 1; i >= 0; i--) {
    swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}

int main()
{
    vector<sampleData> samples = readCSV();
    
    int choice;
    
    
    cout<<"1.insertion sort"<<endl;
    cout<<"2.merge Sort"<<endl;
    cout<<"3.quick Sort"<<endl;
    cout<<"4.quickSort hybrid"<<endl;
    cout<<"5.heap Sort"<<endl;
    cout<<"0.exit"<<endl;
    cout<<"enter a number : ";
    cin >> choice;
    cout<<"\n;";
    
    if (choice == 1){
        cout<<"insertion sort :"<<endl;
        clock_t start, end;
        start = clock();
        cout << "Sample Counts:" << samples.size() << endl;
        insertion_sort(samples, samples.size());
        writeCSV("output_insertionsort.csv", samples);
        end = clock();

        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        cout << "Time taken by program is : " << fixed
                << time_taken << setprecision(5);
        cout << " sec " << endl;
       
        }
    if (choice == 2)
    {
        cout<<"mergeSort :"<<endl;
        clock_t start2, end2;
        start2 = clock();
        cout << "Sample Counts:" << samples.size() << endl;
        mergeSort(samples);;
        writeCSV("output_mergesort.csv", samples);
        end2 = clock();

        double time_taken2 = double(end2 - start2) / double(CLOCKS_PER_SEC);
        cout << "Time taken by program is : " << fixed
                 << time_taken2 << setprecision(5);
        cout << " sec " << endl;
    
    }
        if (choice == 3){
                    cout<<"quick Sort :"<<endl;
                    clock_t start3, end3;
                    start3 = clock();
                    cout << "Sample Counts:" << samples.size() << endl;
                    quickSort(samples, 0, samples.size() - 1);
                    writeCSV("output_quicksort.csv", samples);
                    end3 = clock();

                    double time_taken3 = double(end3 - start3) / double(CLOCKS_PER_SEC);
                    cout << "Time taken by program is : " << fixed
                         << time_taken3 << setprecision(5);
                    cout << " sec " << endl;
            
        }
    if (choice == 4){
                cout<<"quickSort hybrid :"<<endl;
                clock_t start4, end4;
                start4 = clock();
                cout << "Sample Counts:" << samples.size() << endl;
                quickSort_hybrid(samples, 0, samples.size() - 1);
                writeCSV("output_quicksorthybrid.csv", samples);
                end4 = clock();

                double time_taken4 = double(end4 - start4) / double(CLOCKS_PER_SEC);
                cout << "Time taken by program is : " << fixed
                     << time_taken4 << setprecision(5);
                cout << " sec " << endl;
        
    }
    if (choice == 5){
                cout<<"heap Sort :"<<endl;
                clock_t start5, end5;
                start5 = clock();
                cout << "Sample Counts:" << samples.size() << endl;
                heapSort(samples, samples.size() - 1);
                writeCSV("output_heapsort.csv", samples);
                end5 = clock();

                double time_taken5 = double(end5 - start5) / double(CLOCKS_PER_SEC);
                cout << "Time taken by program is : " << fixed
                     << time_taken5 << setprecision(5);
                cout << " sec " << endl;
        
    }
    if (choice ==0){
        return 0;
    }
    return 0;
}
