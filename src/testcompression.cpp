#include <string>
#include <iostream>
#include <math.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;


char bin_hex(std::string bin){
	int ent=0;
	for(size_t i=0;i<4;i++){
		if (bin[3-i]=='1'){
			ent+=pow(2,i);
		}
	}
	char ret;
	if(ent<10){
		ret=ent+'0';
	}
	else{
		ret=ent+87;
	}
	return ret;


}

std::string hex_bin(char hex){
	int ent;
	if(((size_t)hex)>90){
		ent=(int)hex-87;
	}
	else{
		ent=hex-'0';
	}
	std::string ret2;
	for(size_t i=0;i<4;i++){
		if (ent%2==1){
			ret2.push_back('1');
		}
		else{
			ret2.push_back('0');			
		}
		ent/=2;
	}
	std::string ret;
	for(size_t i=0;i<4;i++){
		ret.push_back(ret2[3-i]);
	}
	return ret;

}



std::string compression(std::string text){
	std::string ret_string="";
	for (size_t i=0;i<text.size();i++){
		std::string bin;
		char act=text[i];
		size_t asc=act;
		for (size_t j=0;j<8;j++){
			if (asc%2==1){
				bin.push_back('1');
			}
			else{
				bin.push_back('0');			
			}
			asc/=2;
		}
		ret_string.push_back(bin_hex(bin.substr(0,4)));
		ret_string.push_back(bin_hex(bin.substr(4,4)));
		
	
	}
	
	return ret_string;

}

std::string decompression(std::string hexa){
	size_t n=hexa.size()/2;
	std::string ret;
	for(size_t i=0;i<n;i++){
		std::string bin2;
		std::string bin;
		bin2.append(hex_bin(hexa[i*2]));
		bin2.append(hex_bin(hexa[i*2+1]));
		int ent=0;
		for(size_t j=0;j<8;j++){
			bin.push_back(bin2[7-j]);
		}
		for(size_t j=0;j<8;j++){
			if(bin[7-j]=='1'){
				ent+=pow(2,j);
			}
		}
		ret.push_back((char)ent);
	}
	return ret;

}

/*int main(){

char a='A';
size_t b=a;
std::cout<<b;
std::string bin;
size_t asc=a;
for (size_t j=0;j<8;j++){
	if (asc%2==1){
		bin.push_back('1');
	}
	else{
		bin.push_back('0');			
	}
	asc/=2;
}
std::cout<<std::endl<<compression("ABC");
std::cout<<std::endl<<decompression("8242c2");



}*/

PYBIND11_MODULE(testcompression, m) {
    m.doc() = "compression and decompression algorithm for cdt";

    m.def("compression", &compression);
	m.def("decompression",&decompression);
}
