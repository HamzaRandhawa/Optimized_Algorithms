#include <iostream>
#include <vector>
#include <Math.h>
#include <list>
#include <map>
#include <fstream>

using namespace std;

void Print(vector<int> V, string name="")
{
	cout << "\nVector Array "<< name<<" : \n\n";
	for (int i = 0; i < V.size(); i++)
	{
		cout << "V [" << i << "] : " << V[i] << "\n";
	}
}

// 1.1
void Tower_of_Hanoi_App_1(int n, string src, string helper, string dest)
{
	if (n == 0) 
		return;
	
	Tower_of_Hanoi_App_1(n - 1, src, dest, helper);	// Source to hepler Using dest as helper
	cout << "\nMove Slab " << n << " from " << src << " to " << dest;
	Tower_of_Hanoi_App_1(n - 1, helper, src, dest);	// hepler to dest Using Src as Helper
}

// 1.2
void Tower_of_Hanoi_App_2(int n, string src, string helper, string dest)
{
	if (n == 0)
		return;

	Tower_of_Hanoi_App_1(n - 1, src, helper, dest);	// Source to Dest Using helper as helper
	cout << "\nMove Slab " << n << " from " << src << " to " << helper;
	Tower_of_Hanoi_App_1(n - 1, dest,  helper, src);	// Dest to Src Using helper as Helper
	cout << "\nMove Slab " << n << " from " << helper << " to " << dest;
	Tower_of_Hanoi_App_1(n - 1, src, helper, dest);	// Source to Dest Using helper as helper
}

void Task_1()
{
	string src = "Source", helper = "Helper", dest = "Destination";
	int N;
	cout << "\nEnter Number of Slabs : "; cin >> N;

	int choice;
	cout << "\n Approach 1 : Less Steps"
		<< "\n Approach 2: More Steps";

	cout << "\nWhich Approach (Enter Number) : ";
	cin >> choice;

	switch (choice)
	{
	case 1:
		Tower_of_Hanoi_App_1(N, src, helper, dest);
		break;
	case 2:
		Tower_of_Hanoi_App_2(N, src, helper, dest);
		break;
	}
}

// ________________________________________________________

int BSrec(vector<int> V, int s, int e, int T)
{
	int mid = (s + e) / 2;
	if (s > e)
	{
		return -1;
	}
	if (V[mid] == T)
	{
		return mid;
	}
	else if (T > V[mid])		// Reverse as Matrix Rows are in Descending Order
	{
		return BSrec(V, mid + 1, e, T);
	}
	else if (T < V[mid])
	{
		return BSrec(V, s, mid - 1, T);
	}
}
int Binary_Search(vector<int> V, int T)
{
	return BSrec(V, 0, V.size() - 1, T);
}

void Merge(vector<int>& C, const vector<int>& A, const vector<int>& B)
{
	int as = A.size(), bs = B.size();
	int cs = as + bs;

	int ai = 0, bi = 0, ci = 0;

	while (ci < cs)
	{
		if (ai >= as)
		{
			while (bi < bs)
			{
				C[ci++] = B[bi++];
			}
			return;
		}

		if (bi >= bs)
		{
			while (ai < as)
			{
				C[ci++] = A[ai++];
			}
			return;
		}
		if (A[ai] < B[bi])
			C[ci++] = A[ai++];
		else
			C[ci++] = B[bi++];
	}
}

void Merge_Sort(vector<int>& V)
{
	if (V.size() == 1)
		return;

	vector<int> L(V.begin(), V.begin() + V.size() / 2), R(V.begin() + V.size() / 2, V.end());
	Merge_Sort(L);
	Merge_Sort(R);

	Merge(V, L, R);
}

void Task_2_a()
{
	int x;		vector<int> V(100);
	for (int i = 0; i < V.size(); i++)
	{
		V[i] = (rand() % 100) + 1;
	}
	Print(V);
	Merge_Sort(V);		// O (N. Log N)
	Print(V);

	cout << "\nEnter X : "; cin >> x;

	int temp;
	int j;
	for (int i = 0; i < V.size(); i++)
	{
		if (V[i] == 7)
		{
			temp = 1;
		}
		temp = x - V[i];
		if (temp > 0)		// V[j] will be searched when V[i], is not greater than X  
		{					
			j = Binary_Search(V, temp);

			if (j != -1 && j != i)
			{
				cout << "Found : \nV [" << i << "] + V [ " << j << "]\n = " << V[i] << " + " << V[j] << " = " << x;
				return;
			}
		}
		else
		{
			cout << "\nNo Such Values Found!";
			return;
		}
	}
	cout << "\nNo Such Values Found!";
}
void Task_2_b()
{
	int x;		vector<int> V(100);
	for (int i = 0; i < V.size(); i++)
	{
		V[i] = (rand() % 100) + 1;
	}
	Print(V);
	Merge_Sort(V);		// O (N. Log N)
	Print(V);

	cout << "\nEnter X : "; cin >> x;

	int s = 0, e = V.size() - 1;
	int temp;
	while (s < e)
	{
		temp = V[s] + V[e];
		if (temp == x )
		{
			cout << "Found : \nV [" << s << "] + V [ " << e << "]\n = " << V[s] << " + " << V[e] << " = " << x;
			return;
		}
		if (temp > x)
			e--;
		else if (temp < x)
			s++;
	}
	cout << "\nNo Such Values Found!";
}

void Task_2_c()
{
	vector<int> V(100), V2(100);
	V[0] = 2, V2[0] = 5;
	for (int i = 1; i < V.size(); i++)
	{
		V[i] = V[i-1] + 2;
	}
	for (int i = 1; i < V2.size(); i++)
	{
		V2[i] = V2[i-1] + 5;
	}

	Merge_Sort(V);		// O (N. Log N)
	Merge_Sort(V2);		// O (N. Log N)

	Print(V,"V");
	Print(V2, "V2");

	list<int> l;
	vector<int> overlapping;

	for (int i = 0; i < V.size(); i++)
	{
		if (Binary_Search(V2, V[i]) != -1)
		{		
			l.push_back(V[i]);
			overlapping.push_back(V[i]);
		}
	}

	cout <<"\nOverlapping Array with Size : "<< l.size()<<"\n\n";

	for (int i = 0; i < overlapping.size(); i++)
	{
		cout << overlapping[i]<<"\n";
	}

}

void Task_2()
{
	int choice;
	cout << "\n Option 1 : A[i] + A[j] = x		O (N.Log n)"
		<< "\n Option 2 : A[i] + A[j] = x		O (N)"
		<< "\n Option 3 : Overlapping			O (N.Log n)"
		<< "\n Option 4 : Overlapping			O (N)";

	cout << "\nWhich Approach (Enter Number) : ";
	cin >> choice;

	switch (choice)
	{
	case 1:
		Task_2_a();
		break;
	case 2:
		Task_2_b();
		break;
	case 3:
		Task_2_c();
		break;
	case 4:
		break;
	}
}
// __________________________________________________________

void Task_3()
{
	vector<int> V(1000);
	for (int i = 0; i < V.size(); i++)
	{
		V[i] = (rand() % 100) + 1;
	}
	map<int, int> mapv;

	for (int i = 0; i < V.size(); i++)
	{
		if (mapv.find(V[i]) == mapv.end())
		{
			mapv[V[i]] = 1;
		}
		else
			mapv[V[i]]++;
	}

	int c = 0;
	for (auto i = mapv.begin(); i != mapv.end(); i++)
	{
		int s = i->second;
		for (int  j = 0; j < s; j++,c++)
		{
			V[c] = i->first;
		}
	}

	Print(V, "Array V after Sorting");
}

// __________________________________________________
//4

int Check_Shifting(vector<int> V, int s, int e)
{
	if (s >= e)
		return e+1;
	int mid = (s + e) / 2;

	if (V[mid] < V[s])			//	Disorder is on the left side
	{
		return Check_Shifting(V, s, mid - 1);
	}
	else if (V[mid] > V[e])		// Disorder is on the right side
	{
		return Check_Shifting(V, mid + 1, e);
	}
	else
		return e-1;
}
void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
void Reverse_Shift_Right(vector<int> &V, int shift_start_index)
{
	int si = shift_start_index, s = 0;

	while (si != V.size() )
	{
		Swap(V[s], V[si]);
		s++, si++;
	}
	while (s != V.size())	// for the last remaning set, which are brought from one end to other
	{
		Swap(V[s], V[V.size() - 1]);
		s++;
	}
}

void Reverse_Shift_Left(vector<int>& V, int shift_start_index)
{
	int ei = shift_start_index, e = V.size() - 1;

	while (ei != -1)
	{
		Swap(V[e], V[ei]);
		e--, ei--;
	}
	while (e != 1)			// for the last remaning, which are brought from one end to other
	{
		Swap(V[e], V[0]);
		e--;
	}
}

void Print_2(vector<int> V, string msg ="")
{
	cout << "\n" << msg<<" : \n";
	for (int i = 0; i < V.size(); i++)
	{
		cout << V[i] << "\t";
	}
}

void Task_4()
{
	ifstream fin("file4_2.txt");
	int n;
	fin >> n;
	vector<int> V(n);

	for (int i = 0; i < n; i++)
	{
		fin >> V[i];
	}

	Print(V, "Array Read ");
	Print_2(V, "Array Read ");

	int mid = V.size() / 2;
	int si= Check_Shifting(V, 0, V.size() - 1);

	if (si > mid)
	{
		cout << "\n\nArray is shifted towards left " << V.size() - (si-1) << " times and maximum is at index " << si-2 ;
		Reverse_Shift_Left(V, si-1);
	}
	else
	{
		cout << "\n\nArray is shifted towards right " << si+2 << " times and maximum is at index " << si+1;
		Reverse_Shift_Right(V, si+2);
	}

	Print(V, "\nAfter Reversing");
	Print_2(V, "\nAfter Reversing");

	//cout << "\n\nDisorder at : " << si;
}

void Task_5()
{
	vector<int> V(15);
	for (int i = 0; i < V.size(); i++)
	{
		V[i] = 20 - rand() % 33;
	}
	Print_2(V, "\nInitialized Array");

	vector<int> maxSumV(V.size());
	vector<int> maxSiV(V.size());

	int maxSum = maxSumV[0] = V[0];
	int maxEi = 0, maxSi = maxSiV[0] = 0;

	for (int i = 1; i < V.size(); i++)
	{
		if (V[i] > V[i] + maxSumV[i - 1])
		{
			maxSumV[i] = V[i];
			maxSiV[i] = i;
		}
		else
		{
			maxSumV[i] = V[i] + maxSumV[i - 1];
			maxSiV[i] = maxSiV[i - 1];
		}
		if (maxSumV[i] > maxSum)
		{
			maxSum = maxSumV[i];
			maxSi = maxSiV[i];
			maxEi = i;
		}
	}

	cout << "\n\nMaximum Contigous Sum is " << maxSum << "\n with Starting Index : " << maxSi
		<< "\n and Ending Index :" << maxEi;
}

int BSrec_matching(vector<int> V, int s, int e)
{
	int mid = (s + e) / 2;
	if (s > e)
	{
		return -1;
	}
	if (V[mid] == mid)
	{
		return mid;
	}
	else if (V[mid] < mid)		
	{
		return BSrec_matching(V, mid + 1, e);
	}
	else if (V[mid] > mid)
	{
		return BSrec_matching(V, s, mid - 1);
	}
}

int Give_matching_index(vector<int> V)
{
	if (V[0] == 0)	return 0;

	int i;
	for (i = 1; i < V.size(); i*=2)
	{
		if (V[i] < 0) 
			continue;

		else if (V[i] > i)
		{
			return BSrec_matching(V, i / 2, i);
		}
	}
	return BSrec_matching(V, i / 2, V.size()-1);
}
void Task_7()
{
	vector<int> V(10000);
	for (int i = 0; i < V.size(); i++)
	{
		V[i] = 10000 - rand() % 11000;
	}
	Merge_Sort(V);

	//Print(V, "\nAfter Sorting : \n");

	int mi = Give_matching_index(V);
	if (mi == -1)
		cout << "\nNo such Index Found such that V[i] = i";
	else
		cout << "\nV [" << mi << "] = " << mi;
}

int Give_Sum(vector<int> V)
{
	int sum = 0;
	for (int i = 0; i < V.size(); i++)
	{
		sum += V[i];
	}
	return sum;
}

void Task_8()
{
	vector<int> X(10);
	vector<int> Y(10);

	for (int i = 0; i < X.size(); i++)
	{
		X[i] = rand() % 100;
		Y[i] = rand() % 100;
		/*X[i] = i + 1;
		Y[i] = i;*/
	}
	Merge_Sort(X);
	Merge_Sort(Y);

	int Xsum = Give_Sum(X);
	int Ysum = Give_Sum(Y);

	for (int i = 0; i < X.size(); i++)
	{
		int T = Ysum + X[i] - (Xsum - X[i]);		//Y + xi - (X-xi) = 2yj // 2T
		int index = Binary_Search(Y, T/2);

		if (index != -1)
		{
			cout << "'X[i] = X [" << i << " ] = " << X[i] << " ' and Y[j] = Y [" << index << "] = " << Y[index]
				<< " ' can be swapped to equate 'X = " << Xsum << " ' and 'Y = " << Ysum << " '";
			return;
		}
		
	}
	cout << "No Such Values exist!";

}
void Menu()
{
	cout <<
		"Task No 1 : Tower of Hanoi\n"
		"Task No 2 : Ai + Aj = x\n"
		"Task No 3 : Sorting with K different Values		O(N.Log K)\n"
		"Task No 4 : Findig and Reversing Circular Shifting\n"
		"Task No 5 : Contiguous Sub-Array with Maximum Sum\n"
		//"Task No 6 : \n"
		"Task No 6 : Index at Which V[i] = i\n"

		"Task No 7 : Which X[i] and Y[j] Values can be swapped to equate X and Y \n"

		<< "\nTask No 10 : Exit";

	cout << "\n\nEnter Task No : ";

}


void main()
{
	int choice, N;

	while (true)
	{
		Menu();
		cin >> choice;

		switch (choice)
		{
		case 1:
			Task_1();
			break;
		case 2:
			Task_2();
		case 3:
			Task_3();
			break;
		case 4:
			Task_4();
			break;
		case 5:
			Task_5();
			break;
		case 6:
			//Task_6();
			break;
		case 7:
			Task_7();
			break;
		case 8:
			Task_8();
			break;
		case 10:
			break;
		}
		cout << "\n\n";
	}

	cout << "\n\n";
}
