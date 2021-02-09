using namespace std;

vector<string> BFGC(n){
	if(n==1){
		vector<string> L;
		L.push_back("0");
		L.push_back("1");
		return L;
	}
	else{
		L1=BFGC(n-1);
		L2=reverse(L1);
		for(auto i=L1.begin(); i!=L1.end(); i++){
			*i="0"+*i;
		}
		for(auto j=L2.begin(); j!=L2.end(); j++){
			*j="1"+*j;
		}
		L1.insert(L1.end(), L2.begin(), L1.end());
	}
	return L1;
}