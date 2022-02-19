#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <memory.h>

using namespace std;


int main(int argc, char**argv) 
{
	string line;

  	fstream sin("equation.in", sin.in);

	getline(sin, line);
	istringstream iss(line);

	int x, y, z;
	iss >> x;
	iss >> y;
	iss >> z;
//	cout<<x<<' '<<y<<' '<<z<<' '<<y/z<<endl;

	std::fstream sout("equation.out", sout.out);

	if (x == y + z) {
		sout<< x << '=' << y << '+' << z << endl;
	} else {
		if (x == y - z) {
			sout<< x << '=' << y << '-' << z << endl;
		} else {
			if (x == y * z) {
				sout<< x << '=' << y << '*' << z << endl;
			} else {
				if (x == y / z && y%z == 0) {
					sout<< x << '=' << y << '/' << z << endl;
				} else {
					if (x + y == z) {
						sout<< x << '+' << y << '=' << z << endl;
					} else {
						if (x - y == z) {
							sout<< x << '-' << y << '=' << z << endl;
						} else {
							if (x * y == z) {
								sout<< x << '*' << y << '=' << z << endl;
							} else {
								sout<< x << '/' << y << '=' << z << endl;
							}
						}
					}
				}
			}
		}
	}

	return 0;
}