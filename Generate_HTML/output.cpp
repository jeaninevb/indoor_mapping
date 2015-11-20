#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <Eigen/StdVector>
#include <gflags/gflags.h>

DEFINE_string(directory, "duc01,duc02", "Directory name.");
DEFINE_double(parameter, 2.4, "random.");


using namespace std;
using namespace Eigen;

void generateHtml(const map<string, Vector2d>& expected_uv_data, string& html_data, string dir) {
    
    
    string start = " <!DOCTYPE html><html><style>img {position: absolute;}</style><body><script>function inputPanoramic(message) {var myWindow = window.open(\"test.html?msg=\" + message,\"\",\"width=1200, height=600\");} </script> <img src= \""+dir+ "/floor.jpg\" \"style=\"z-index: -1;left: 0px;top: 0px;\"> ";
    html_data +=start;//starting html
    
    string formatFirst = "<a onclick=\"inputPanoramic('"+dir+"/Panoramic/";
    //duc000
    string formatSecond = ".jpg')\"> <img src=\"info.png\" style=\"z-index: 1; left: ";
    //150      //left
    string coordLeft = "px;top: ";
    //475      //top
    string coordTop = "px;width: 15px;height: 15px;\"></a> ";
    
    //loop through map to get the point
    for (const auto& itr : expected_uv_data)  {
        string tempName = itr.first;
        double tempLeft = (itr.second)[0];
        double tempTop = (itr.second)[1];
        html_data += formatFirst + tempName + formatSecond + to_string(tempLeft) + coordLeft + to_string(tempTop) + coordTop;
    }
    
    html_data += "</body></html>";
    
}


int main(int argc, char * argv[]) {
    google::ParseCommandLineFlags(&argc, &argv, true);
    
    //cout << "start: " <<FLAGS_directory << endl;
   
    
    map<string,Vector2d> expected_uv_data;
	
	string path = FLAGS_directory + "/XY_FL_2d.txt";
	
	
    ifstream coordinate_data(path);

   if(coordinate_data.is_open()){
    	
    	string line;
    	int total;
    	
    	//get the int at the first line that
    	//says how many total coordinates are in file
    	getline(coordinate_data, line);
    	
    	if(stringstream(line) >> total){
    		
    		for(int i = 0; i < total; i++){
    		
    			string scan_id;
    			string file_line;
    			double coordX;
    			double coordY;
    			
    			//extract "duc###"
    			getline(coordinate_data, scan_id, ':');
    			//extract coordinates
    			getline(coordinate_data, file_line); 
    			
    			stringstream(file_line) >> coordX >> coordY;
    			Vector2d xy_data(coordX, coordY);
    			expected_uv_data.insert(pair<string, Vector2d>(scan_id, xy_data));

    		}
    	
    	}
    
    }
    

    
    //call function and create html file.
    ofstream myfile("duc.html");
    string html_data;
    generateHtml(expected_uv_data, html_data, FLAGS_directory);
    myfile << html_data;
    myfile.close();
    
    
    return 0;
}


