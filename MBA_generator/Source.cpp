#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <windows.h>
#include <time.h>
#include <random>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;


typedef enum __BOOLOPERATIONS
{
	_X =		1,
	_Y =		2,
	_AND =		4,
	_OR =		8,
	_NOT =		16,
	_XOR =		32,
	
}BoolOperations;

typedef enum __OPERAND_NOT
{
	_NOTX = 64,	//x has not
	_NOTY = 128	//y has not
}OPERAND_NOT;

WORD stBoolExp[16] = {
	_X,
	_Y,
	_NOTX,
	_NOTY,
	_X | _AND | _Y,
	_X | _OR | _Y,
	_X | _XOR | _Y,
	_NOTX | _AND | _Y,
	_X | _AND | _NOTY,
	_NOTX | _AND | _NOTY,
	_NOTX | _OR | _Y,
	_X | _OR | _NOTY,
	_NOTX | _OR | _NOTY,
	_NOTX | _XOR | _Y,
	_X | _XOR | _NOTY,
	_NOTX | _XOR | _NOTY
};

typedef struct __BOOLEXPRESSION
{
	BYTE dwFirstNot;			//first not flag
	BYTE dwSecondNot;			//second not flag
	BoolOperations dwBoolOp;			//boolean operation
	__BOOLEXPRESSION* PosNext;
}BoolExpression, * PBoolExpression;


/*void temp()
{
	HMODULE hModule = GetModuleHandle();
	PBYTE NewMemory = NULL;
	if (hModule)
	{
		HRSRC hRes = FindResource(hModule, MAKEINTRESOURCE(IDR_BOOLBOOL), RT_RCDATA);
		if (hRes != NULL)
		{
			HGLOBAL hResLoad = LoadResource(hModule, hRes);
			if (hResLoad)
			{
				DWORD dwRcSize = SizeofResource(GetModuleHandle(NULL), hRes);
				LPVOID lpResLock = LockResource(hResLoad);
				if (lpResLock)
				{
					NewMemory = (PBYTE)malloc(dwRcSize);
					CopyMemory(NewMemory, lpResLock, dwRcSize);
				}
			}
		}

		FreeLibrary(hModule);
	}
}
*/


const char* stSymbols[16] = {
	"(x)",
	"(y)",
	"(~x)",
	"(~y)",
	"(x & y)",
	"(x | y)",
	"(x ^ y)",
	"(~x & y)",
	"(x & ~y)",
	"(~x & ~y)",
	"(~x | y)",
	"(x | ~y)",
	"(~x | ~y)",
	"(~x ^ y)",
	"(x ^ ~y)",
	"(~x ^ ~y)"
};

template<typename T>
void pop_front(std::vector<T>& v)
{
	if (v.size() > 0) {
		v.erase(v.begin());
	}
}

bool st1(bool x, bool y)
{
	return x;
}
bool st2(bool x, bool y)
{
	return y;
}
bool st3(bool x, bool y)
{
	return (!(x));
}
bool st4(bool x, bool y)
{
	return (!(y));
}
bool st5(bool x, bool y)
{
	return (x && y);
}
bool st6(bool x, bool y)
{
	return ((x) || (y));
}
bool st7(bool x, bool y)
{
	return (x ^ y);
}
bool st8(bool x, bool y)
{
	return (!(x) && (y));
}
bool st9(bool x, bool y)
{
	return ((x) && !(y));
}
bool st10(bool x, bool y)
{
	return (!(x) && !(y));
}
bool st11(bool x, bool y)
{
	return (!(x) || y);
}
bool st12(bool x, bool y)
{
	return ((x) || !(y));
}
bool st13(bool x, bool y)
{
	return (!(x) || !(y));
}
bool st14(bool x, bool y)
{
	return (!(x) ^ (y));
}
bool st15(bool x, bool y)
{
	return (x ^ !(y));
}
bool st16(bool x, bool y)
{
	return (!(x) ^ !(y));
}

bool (*funcptr[])(bool, bool) = { st1, st2, st3, st4, st5, st6, st7, st8, st9, st10, st11, st12, st13, st14, st15, st16 };

void print_arr(bool** tb, int r, int c)
{
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			printf("%d ", tb[i][j]);
		}
		printf("\n");
	}
}

int find_max_vecSize(vector<vector<WORD>> vvw)
{
	int max = vvw.at(0).size();
	for (int i = 0; i < vvw.size(); i++)
	{
		if (vvw.at(i).size() > max)
		{
			max = vvw.at(i).size();
		}
	}
	return max;
}

void CreateMBATableFile(vector<vector<WORD>> vwBoolExprs, vector<vector<string>> vStSymb)
{
	FILE* iFile;
	vector<WORD> v;
	vector<string> sym;
	int maxSize = 0;
	fopen_s(&iFile, "c:\\Users\\Hossein\\Desktop\\TableMBAtbl.h", "wb");
	maxSize = find_max_vecSize(vwBoolExprs);
	fprintf(iFile, "#include <windows.h>\n\n#define _ROW_ %d\n#define _COLUMN_ %d\nWORD mba_table[ %d ][ %d ] = \n{\n", vwBoolExprs.size(), maxSize, vwBoolExprs.size(), maxSize);

	
	while (vwBoolExprs.size())
	{
		v = vwBoolExprs.front();
		sym = vStSymb.front();
		for (int i = 0; i < maxSize; i++)
		{
			if (i == 0)
			{
				fprintf(iFile, "{0x%04x", v.at(i));
			}
			else if (i == maxSize - 1)
			{
				if (i < v.size())
					fprintf(iFile, ", 0x%04x}", v.at(i));
				else
					fprintf(iFile, ", 0x%04x}", 0x0000);
			}
			else if (i < v.size())
			{
				fprintf(iFile, ", 0x%04x", v.at(i));
			}
			else if (i >= v.size())
			{
				fprintf(iFile, ", 0x%04x", 0x0000);
			}
		}
		if (vwBoolExprs.size() != 1)
		{
			fprintf(iFile, "%s", ", \n");
		}
		else
		{
			fprintf(iFile, "%s", "\n");
		}
		for (int i = 0; i < maxSize; i++)
		{
			if (i == 0)
			{
				fprintf(iFile, "//{%s ", sym.at(i).c_str());
			}
			else if (i == maxSize - 1)
			{
				if (i < sym.size())
					fprintf(iFile, ", %s}\n", sym.at(i).c_str());
				else
					fprintf(iFile, ", %s}\n", "Undf");
			}
			else if (i < sym.size())
			{
				fprintf(iFile, ", %s", sym.at(i).c_str());
			}
			else if (i >= sym.size())
			{
				fprintf(iFile, ", %s", "Undf");
			}
			pop_front(vStSymb.front());
		}
		pop_front(vwBoolExprs);
		pop_front(vStSymb);
	}
	fprintf(iFile, "%s", "\n};");
	fclose(iFile);
}


void updateBoolExpCoef(vector<vector<int>> vec, vector<vector<WORD>> expr, int c, vector<vector<WORD>>* vwBoolExprs)
{
	vector<int> vSol;
	vector<WORD> ev;
	vector<WORD> vw;
	WORD wBoolExpr = 0;
	while(vec.size())
	{
		vSol = vec.front();
		ev = expr.front();
		for (int j = 0; j < vSol.size(); j++)
		{
			wBoolExpr = ev.at(j) << 8;
			wBoolExpr |= (BYTE)vSol.at(j);
			vw.push_back(wBoolExpr);
		}
		vwBoolExprs->push_back(vw);
		vw.clear();
		pop_front(vec);
		pop_front(expr);
	}

}

void shufflee(int size)
{
	int index1 = 0;
	int index2 = 0;
	bool (*funcAddress)(bool x, bool y) = NULL;
	const char* strSymb = NULL;
	WORD boolExp = NULL;

	for (int i = 0; i < size; i++)
	{
		index1 = (rand() % (size - 7)) + 7;
		funcAddress = funcptr[index1];
		strSymb = stSymbols[index1];
		boolExp = stBoolExp[index1];
		
		index2 = (rand() % (size - 7)) + 7;
		funcptr[index1] = funcptr[index2];
		stSymbols[index1] = stSymbols[index2];
		stBoolExp[index1] = stBoolExp[index2];
		
		funcptr[index2] = funcAddress;
		stSymbols[index2] = strSymb;
		stBoolExp[index2] = boolExp;
	}
	
}

bool** init(int r, int* c)
{
	//add stages to the list blow
	
	/*for (int i = 0; i < 16; i++)
	{
		printf("[%x] ", funcptr[i]);
	}
	printf("\n\n");
	for (int i = 0; i < 16; i++)
	{
		printf("[%s] ", stSymbols[i]);
	}
	printf("\n\n");
	for (int i = 0; i < 16; i++)
	{
		printf("[%x] ", stBoolExp[i]);
	}
	printf("\n\n");*/
	shufflee(16);
	/*for (int i = 0; i < 16; i++)
	{
		printf("[%x] ", funcptr[i]);
	}
	printf("\n\n");
	for (int i = 0; i < 16; i++)
	{
		printf("[%s] ", stSymbols[i]);
	}
	printf("\n\n");
	for (int i = 0; i < 16; i++)
	{
		printf("[%x] ", stBoolExp[i]);
	}
	printf("\n\n");*/
	*c = rand() % 6 + 5;
	printf("\n\n");
	bool** table = new bool* [r];
	for (int i = 0; i < r; i++)
	{
		table[i] = new bool[*c];
	}
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < *c; j++)
		{
			table[i][j] = 0;
		}
	}

	//print_arr(table, r, *c);

	//printf("\n\n");
	if (r == 4)
	{
		for (int i = 0; i < *c; i++)
		{
			for (int j = 0; j < r; j++)
			{
				//printf("*funptr = %d, ", (*funcptr[i])(((j) & 2) >> 1, (j) & 1));
				table[j][i] = (*funcptr[i])(((j) & 2) >> 1, (j) & 1);
				//printf("*table = %d,", table[i][j]);
				//print_arr(table, r, *c);
				//printf("----------------\n");
			}
			
		}
	}
	//print_arr(table, r, *c);
	return table;

}

int getSum(bool** table, int *v, int r, int c)
{
	bool flag = 1;
	unsigned int sum = 0;
	for (int i = 0; i < r; i++)
	{
		sum = 0;
		for (int j = 0; j < c; j++)
		{
			sum += (int)((int)((table[i][j])) * v[j]);
		}
		if (sum != 0)
		{
			flag = 0;
		}

	}
	return flag;
}

void print_1darr(int* v, int c)
{
	for (int i = 0; i < c; i++)
	{
		printf("%4d", v[i]);
	}
	printf("\n");
}
vector<string> print_symb(int* v, int c)
{
	vector<string> res;
	string eq = "";
	for (int i = 0; i < c; i++)
	{
		eq = "";
		printf("%2d*%s ", v[i], stSymbols[i]);
		eq += to_string(v[i]) + "*" + stSymbols[i];
		if (i != c - 1)
		{
			printf("+ ");
			//eq += "+ ";
		}
		res.push_back(eq);
	}
	printf("\n\n");
	return res;
}
bool check(int* v, int c, int max)
{
	bool res = 0;
	for(int i = 0; i < c; i++)
	{
		if (v[i] != max)
		{
			res = 1;
		}
	}
	return res;
}
bool check_zero(int* v, int c)
{
	bool res = 0;
	for (int i = 0; i < c; i++)
	{
		if (v[i] == 0)
		{
			res = 1;
		}
	}
	return res;
}
void solve(bool ** table, int r, int c, int min, int max, vector<vector<int>> *solutions, vector<vector<string>> *vStSymbs, vector<vector<WORD>> *vStExps)
{
	int* v = new int[c];
	int counter = 0;
	for (int i = 0; i < c; i++)
	{
		v[i] = min;
	}
	while(1)
	{
		for (int j = 0; j < c - 1; j++)
		{
			if (v[j] == max + 1)
			{
				v[j] = min;
				v[j + 1] += 1;
			}
		}
		if (getSum(table, v, r, c) == 1 && !check_zero(v, c))
		{
			printf("[%d] ", counter+1);
			vector<int> solu(v, v + c);
			vector<WORD> expr(stBoolExp, stBoolExp + 16);
			solutions->push_back(solu);
			vStSymbs->push_back(print_symb(v, c));
			vStExps->push_back(expr);
			counter++;
		}
		if (check(v, c, max))
		{
			v[0]++;
		}
		else
		{
			break;
		}
		
	}
	//printf("[+] solution numbers: %d\n", counter);
	//(BYTE bool)(BYTE coff)
	
}
void set_zero(char *buf, int size)
{
	for (int i = 0; i < size; i++)
	{
		buf[i] = 0;
	}
}


int main()
{
	srand(time(NULL));
	int c = 0;
	vector<vector<int>> solutions;
	vector<vector<string>> vStSymbs;
	vector<vector<WORD>> vStExps;
	for (int i = 0; i < 10; i++)
	{
		//create table 4 rows and c column
		bool** table = init(4, &c);
		//solve table with min and max vector value
		solve(table, 4, c, -2, 2, &solutions, &vStSymbs, &vStExps);
	}
	vector<vector<WORD>> vwBoolExpresstions;
	updateBoolExpCoef(solutions, vStExps, c, &vwBoolExpresstions);
	CreateMBATableFile(vwBoolExpresstions, vStSymbs);
}