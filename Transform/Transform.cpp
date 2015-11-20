//===========================================================
// Transform.cpp
//Jeanine Burke and Xinyi Gong
// map 3D coordinates onto floorplan
//===========================================================

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/SparseCholesky>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace Eigen;
using namespace std;


int main(){
	
 SparseMatrix<double> A((2 * 4), 6);
 

 ifstream ifs("matrix_A.txt");

 string line;
 double x;
 double y;
 double z;
 double a;
 double b;
 double c;

 vector<double> rowCoordinates (6);
 
 if(ifs.is_open()){
 	
	for(int i = 0; i < 8; i++){
		
		getline(ifs, line);
		if(!line.empty()){
			
			if(stringstream(line) >>x>>y>>z>>a>>b>>c){
				rowCoordinates.at(0) = x;
				rowCoordinates.at(1) = y;
				rowCoordinates.at(2) = z;
				rowCoordinates.at(3) = a;
				rowCoordinates.at(4) = b;
				rowCoordinates.at(5) = c;
	
			}
		}
		
		for(int j = 0; j < 6; j++){

			A.coeffRef(i, j) = rowCoordinates.at(j);
		}
		
	}

 }


//cout << A << endl;

SparseMatrix<double> new_A (6,6);
new_A = A.transpose()*A; 
//cout << new_A << endl;

VectorXd vectb(8);
vectb <<277.0, 655.0, 570.0, 340.0, 550.0, 510.0, 915.0, 570.0;

//cout << vectb << endl; 

VectorXd new_b (6);

new_b  = A.transpose()*vectb;

//cout << new_b << endl;


//Solve Ax = b

SimplicialCholesky<SparseMatrix<double> > chol(new_A);
VectorXd vect_x = chol.solve(new_b);

//cout << "SOLUTION" << endl;
//cout << vect_x << endl;


///////////////////////////////////////////////////////

//Now, use x to solve for all 2D points from XYZ file


//SparseMatrix<double> A_converted((2 * 4), 6);

cout << "INPUT DATA" << endl;

ofstream duc_XY("XY_FL2_2d.txt");
ifstream large_stream("XYZ_FL2_3d.txt");

vector<int> scan_collector (8);
	
	
	while(!(large_stream.eof())){
		string input;
		int scan_num;
		double scanX;
		double scanY;
		
		int i = 0;
		SparseMatrix<double> A_input((2 * 4), 6);

		while(i < 8){
			
 			vector<double> rowCoordinates1 (6);
			
			
			getline(large_stream, input);

			if(stringstream(input) >> scan_num >> scanX >> scanY){
					
					//keep track of the current scan
					scan_collector.at(i) = scan_num;
					
				//x y 1 0 0 0
 					cout << "SCAN:  " << scan_num << endl;
 					rowCoordinates1.at(0) = scanX;
					rowCoordinates1.at(1) = scanY;
					rowCoordinates1.at(2) = 1.0;
					rowCoordinates1.at(3) = 0.0;
					rowCoordinates1.at(4) = 0.0;
					rowCoordinates1.at(5) = 0.0;
					
					
					for(int j = 0; j < 6; j++){

						A_input.coeffRef(i, j) = rowCoordinates1.at(j);
					}
					
					i++;
 				
 				// 0 0 0 x y 1
 					
 					scan_collector.at(i) = scan_num;

 					rowCoordinates1.at(0) = 0.0;
					rowCoordinates1.at(1) = 0.0;
					rowCoordinates1.at(2) = 0.0;
					rowCoordinates1.at(3) = scanX;
					rowCoordinates1.at(4) = scanY;
					rowCoordinates1.at(5) = 1.0;


					for(int j = 0; j < 6; j++){
						
						
						A_input.coeffRef(i, j) = rowCoordinates1.at(j);
			 					
 					}
 								
					
					i++;
 			
 			}
 								
	}
	
	 			//eight rows have been inserted into A
 			//solve for b in Ax = b
 			
 			cout << "AAAAAAAA" << endl;
			cout << A_input << endl;


			VectorXd input_b(6);

			input_b = A_input * vect_x;

			cout << "bbbbbbb" << endl;
			cout << input_b << endl;
			
			for(int m = 0; m < 8; m++){
				
				if (m%2 == 0){
					
					if(scan_collector.at(m) < 100){
						duc_XY << "duc0" << scan_collector.at(m) << ": " << input_b(m, 0) << " ";
					}
					else{
						duc_XY << "duc" << scan_collector.at(m) << ": " << input_b(m, 0) << " ";
					}
				}
				else{
					duc_XY << input_b(m, 0) <<endl;
				}
			}
			
			
			
			
 }
 
duc_XY.close();





return 0;

}


