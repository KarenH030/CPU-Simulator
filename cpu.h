#ifndef CPU_H
#define CPU_H


#include<vector>
#include<cmath>
#include<map>


std::vector <std::string> keywords {"r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "mov", "add", "sub", "mul", "div", "cmp", "jmp", "je", "jl;", "jg"};



class CPU {

	private:
		std::map <std::string, int> m_map;
		int m_line = 1;

	private:
		
		int  check_keyword(std::string&);
		int string_to_num(std::string&);
		void syntax_error();
	
	public:

		void run();
       		void do_move(std::ifstream&);
		void do_add(std::ifstream&);
		void do_sub(std::ifstream&);
		void do_mul(std::ifstream&);
		void do_div(std::ifstream&);
		void do_jmp(std::ifstream&, std::string&);
		void do_je(std::ifstream&, std::string&);
		void do_jl(std::ifstream&, std::string&);
		void do_jg(std::ifstream&, std::string&);
		int do_cmp(std::ifstream&);

	private:

		bool is_register(std::string&);
		bool is_digit(const char&);
		bool is_label(std::string&);


};



bool CPU::is_register(std::string& token) {
	if (check_keyword(token) >= 0 && check_keyword(token) <= 9) {
		return true;
	}
	return false;
}

bool CPU::is_digit (const char& ch) {
	return (ch >= 48 && ch <= 57);
}

bool CPU::is_label(std::string& str) {
	return (str[str.size() - 1] == ':'); 
}

void CPU::syntax_error() {
	std::cout << "You may have syntax error in line #" <<m_line << std::endl;
}

int CPU::check_keyword(std::string& token) {

	for (int i = 0; i < keywords.size(); ++i) {
		if (keywords[i] == token) {
			return i;
		}
	}
	return -1;
}
int CPU::string_to_num (std::string& str) {
	int num;
	for (int i = 0; i < str.size(); ++i) {
		num += pow(10,(str.size() - 1 - i )) * (str[i] - 48);
	}
	return num;
} 

void CPU::do_move(std::ifstream& fin) {

	std::string str = "";
	fin >> str;
	if (!is_register(str)) {
		syntax_error();
		return;
	}
	std::string tmp = "";
	fin >> tmp;
	if (is_register(tmp)) {
		m_map.erase(str);
		m_map.insert(make_pair(str,m_map[tmp]));
		return;
	}
	if (is_digit(tmp[0])) {
		int num = string_to_num(tmp);
		m_map.erase(str);
		m_map.insert(make_pair(str,num));
		return;
	}
	syntax_error();
	return;
}



void CPU::do_add(std::ifstream& fin) {
	
	std::string str = "";
	fin >> str;
	if (!is_register(str)) {
		syntax_error();
		return;
	}
	std::string tmp = "";
	fin >> tmp;
	if(is_digit(tmp[0])) {
		int num = string_to_num(tmp);
		m_map[str] += num;
		return;
	}
	if (is_register(tmp)) {
		m_map[str] += m_map[tmp];
	        return;	
	}
	syntax_error();
	return;

}

void CPU::do_sub (std::ifstream& fin) {

	std::string str = "";	
		fin >> str;
	if (!is_register(str)) {
		syntax_error();
		return;
	}
	std::string tmp = "";
	fin >> tmp;
	if (is_digit(tmp[0])) {
		int num = string_to_num(tmp);
		m_map[str] -= num;
		return;
	}
	if (is_register(tmp)) {
		m_map[str] -= m_map[tmp];
		return;
	}
	syntax_error();
	return;
}

void CPU::do_mul(std::ifstream& fin) {

std::string str = "";	
		fin >> str;
	if (!is_register(str)) {
		syntax_error();
		return;
	}
	std::string tmp = "";
	fin >> tmp;
	if (is_digit(tmp[0])) {
		int num = string_to_num(tmp);
		m_map[str] *= num;
		return;
	}
	if (is_register(tmp)) {
		m_map[str] *= m_map[tmp];
		return;
	}
	syntax_error();
	return;
}


void CPU::do_div(std::ifstream& fin) {

	std::string str = "";	
		fin >> str;
	if (!is_register(str)) {
		syntax_error();
		return;
	}
	std::string tmp = "";
	fin >> tmp;
	if (is_digit(tmp[0])) {
		int num = string_to_num(tmp);
		m_map[str] /= num;
		return;
	}
	if (is_register(tmp)) {
		m_map[str] /= m_map[tmp];
		return;
	}
	syntax_error();
	return;
}

int CPU::do_cmp(std::ifstream& fin) {

	std::string str = "";
	fin >> str;
	if (!is_register(str)) {
		syntax_error();
		return -1;
	}
	std::string tmp = "";
	fin >> tmp;
	if (is_digit(tmp[0])) {
		int num = string_to_num(tmp);
		if (m_map[str] == num) {
			return 0;
		}
		if (m_map[str] > num) {
			return 1;
		}
		else {
			return 2;
		}

	}
	if (is_register(tmp)) {
		if (m_map[str] == m_map[tmp]) {
			return 0;
		}
		if (m_map[str] > m_map[tmp]) {
			return 1;
		}
		else {
			return 2;
		}
		
	}
	syntax_error();
	return -1;

}


void CPU::run() {
	std::ifstream file;
	std::string file_name;
	do {
		std::cout << "Enter the file name  : ";
		std::cin >> file_name;
		file.open(file_name);
	}
	while(!file.is_open());

	std::string token = "";
	while(!file.eof()) {
		file >> token;
		int keyword = check_keyword(token);
		switch (keyword) {

		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			std::cout << "Error in line #" << m_line << std::endl;
			break;
		case 10:
			do_move(file);
			break;
		case 11:
			do_add(file);
			break;
		case 12:
			do_sub(file);
			break;
		case 13:
			do_mul(file);
			break;
		case 14:
			do_div(file);
			break;
		case 15:
			do_cmp(file);
			break;
		case 16:
			do_jmp(file,file_name);
			break;
		case 17:
			do_je(file,file_name);
			break;
		case 18:
			do_jl(file,file_name);
			break;
		case 19:
			do_jg(file,file_name);
			break;
		case -1:
			if (is_label(token)) {
				m_map.insert(make_pair(token,m_line));	
			}

		}
		++m_line;
	}
}

void CPU::do_jmp(std::ifstream& file, std::string& file_name) {
	std::string str;
	file >> str;
	file.close();
	std::string tmp;
	int line = 1;
	file.open(file_name);
	do {
		std::getline(file,tmp);
		tmp.pop_back();
		if (str == tmp) {
			m_line = line;
			return;
		}		
		++line;
	}while (!file.eof());
	syntax_error();
	return;
}


void CPU::do_je(std::ifstream& fin, std::string& file_name) {

	fin.close();
	fin.open(file_name);
	std::string str;
	int line = 1;
	do {
		if (line == m_line - 1) {
			break;
		}
		++line;
		std::getline(fin,str);
		
	} while (!fin.eof());

	fin >> str;
	if (check_keyword(str) != 15) {
		syntax_error();
		return;
	}
	int check = do_cmp(fin);
	if (check == 0) {
		fin >> str;
		do_jmp(fin,file_name);
		return;
	}
	return;
	
	
	


}

void CPU::do_jl(std::ifstream& fin, std::string& file_name) {

	fin.close();
	fin.open(file_name);
	std::string str;
	int line = 1;
	do {
		if (line == m_line - 1) {
			break;
		}
		++line;
		std::getline(fin,str);
		
	} while (!fin.eof());

	fin >> str;
	if (check_keyword(str) != 15) {
		syntax_error();
		return;
	}
	int check = do_cmp(fin);
	if (check == 2) {
		fin >> str;
		do_jmp(fin,file_name);
		return;
	}
	return;
}

void CPU::do_jg(std::ifstream& fin, std::string& file_name) {

	fin.close();
	fin.open(file_name);
	std::string str;
	int line = 1;
	do {
		if (line == m_line - 1) {
			break;
		}
		++line;
		std::getline(fin,str);
		
	} while (!fin.eof());

	fin >> str;
	if (check_keyword(str) != 15) {
		syntax_error();
		return;
	}
	int check = do_cmp(fin);
	if (check == 1) {
		fin >> str;
		do_jmp(fin,file_name);
		return;
	}
	return;	
}






#endif // CPU.H 
