//#include <pybind11/pybind11.h>

//namespace py = pybind11;

#include <vector>
#include <string>
#include <iostream>

struct arc{
	char bin;
	struct node * father;
	struct node * child;
};

struct node{
	char leaf;
	signed long long freq;
	//struct node * right;
	//struct node * left;
	struct arc right;
	struct arc left;
	size_t pass=0;
};

///////merge sort (decrease)///////
struct proba{
	std::vector<char> ch;
	std::vector<signed long long> nb;
};

struct proba merge(struct proba L1, struct proba L2){
	size_t n1=L1.ch.size();
	size_t n2=L2.ch.size();
	size_t k1=0;
	size_t k2=0;
	struct proba M;
	while(k1!=n1 || k2!=n2){
		if(k1!=n1 && k2!=n2){
			if(L1.nb[k1]<=L2.nb[k2]){
				M.nb.push_back(L2.nb[k2]);
				M.ch.push_back(L2.ch[k2]);
				k2++;
			}
			else{
				M.nb.push_back(L1.nb[k1]);
				M.ch.push_back(L1.ch[k1]);
				k1++;
			}

		}
		else{
			if(k1!=n1){
				M.nb.push_back(L1.nb[k1]);
				M.ch.push_back(L1.ch[k1]);
				k1++;
			}
			else{
				M.nb.push_back(L2.nb[k2]);
				M.ch.push_back(L2.ch[k2]);
				k2++;
			}

		}

	}

	return M;


}

struct proba sort(struct proba L){
	struct proba sol;
	if(L.ch.size()<2){
		sol=L;
	}
	else{
		size_t s=L.ch.size();
		size_t n=L.ch.size()/2;
		std::vector<char> ch1(&(L.ch[0]),&(L.ch[n]));
		std::vector<signed long long> nb1(&(L.nb[0]),&(L.nb[n]));
		std::vector<char> ch2(&(L.ch[n]),&(L.ch[s]));
		std::vector<signed long long> nb2(&(L.nb[n]),&(L.nb[s]));
		struct proba L1;
		struct proba L2;
		/*L1.ch(&(L.ch[0]),&(L.ch[n]));
		L1.nb(&(L.nb[0]),&(L.nb[n]));
		L2.ch(&(L.ch[n]),&(L.ch[s]));
		L2.nb(&(L.nb[n]),&(L.nb[s]));*/
		L1.ch=ch1;
		L1.nb=nb1;
		L2.ch=ch2;
		L2.nb=nb2;
		struct proba sol1=sort(L1);
		struct proba sol2=sort(L2);
		sol=merge(sol1,sol2);
		
	}
	return sol;
}
////////////////////////

struct proba probability(std::string text){
	std::vector<char> uniq;
	std::vector<signed long long> nb_iter;
	char actu;
	size_t k=0;
	while(text.size()!=0){
		k=0;
		actu = text[0];
		uniq.push_back(actu);
		nb_iter.push_back(0);
		while(k!=text.size()){
			if (text[k]==actu){
				nb_iter.back()++;
				text.erase(text.begin()+k);
				k--;
			}
			k++;
		}
	}
	struct proba sortl;
	sortl.ch=uniq;
	sortl.nb=nb_iter;
	//std::vector<char> res = (sort(sortl)).ch;
	struct proba res = sort(sortl);
	return res;

}

struct codage{
	char leaf;
	std::string bin;
};

struct graph_search{
	struct node node;
	size_t pass;
};

class HuffmanTree {

private:

	std::vector<struct node> tree;
	//std::vector<struct arc> arcs;
	struct node * root=nullptr;
	//std::vector<struct node> leafs;
	size_t nb_leaf;

public:

	HuffmanTree(std::string text){
		
		struct proba p=probability(text);



		size_t n=p.ch.size();
		nb_leaf=n;
		signed long long ts=0;
		std::vector<struct node *> roots;
		for (size_t i=0 ;i<n;i++){
			struct node nd;
			nd.freq=p.nb[i];
			nd.leaf=p.ch[i];
			ts+=p.nb[i];
			tree.push_back(nd);
			roots.push_back(&tree.back());
		}
for(size_t i=0;i<roots.size();i++){
	std::cout<<roots[i]->freq<<" ";
}
std::cout<<std::endl;

		//struct node * min1;
		size_t m1;
		//struct node * min2;
		size_t m2;
		size_t rs=roots.size();
		//size_t testt=0; //test
		while(rs!=1){

for(size_t i=0;i<roots.size();i++){
	std::cout<<roots[i]->freq<<" ";
}
std::cout<<std::endl;

			rs=roots.size();
			//rs-=testt; //test
			if((roots[0]->freq)<(roots[1]->freq)){
				m1=0;
				m2=1;
			}
			else{
				m1=1;
				m2=0;
			}
			
			//min1=roots[0];
			//min2=roots[1];
			for(size_t i=2;i<rs;i++){
				if ((roots[i]->freq)<(roots[m2]->freq)){
					if((roots[i]->freq)<(roots[m1]->freq)){
						m2=m1;
						m1=i;
					}
					else{
						m2=i;
					}
				}
			}
			//std::cout<<"ici avant"<<roots.size();
			
			struct node newr;
			newr.leaf=NULL;
			newr.freq=(roots[m1]->freq)+(roots[m2]->freq);
			newr.right.bin='1';
			newr.right.child=&(*roots[m1]);
			newr.left.bin='0';
			newr.left.child=&(*roots[m2]);
			tree.push_back(newr);
std::cout<<"binnn "<<(tree.back().left.child)->leaf<<std::endl;
//std::cout<<"bin "<<((*(roots[m1])).root)->bin<<std::endl;
			//std::cout<<roots[roots.begin()+m1]->freq<<std::endl;
			//roots[m1]=nullptr;
			//roots[m2]=nullptr;
			if(m1>m2){
				roots.erase(roots.begin()+m1);
				roots.erase(roots.begin()+m2);
			}
			else{
				roots.erase(roots.begin()+m2);
				roots.erase(roots.begin()+m1);
			}
			//std::cout<<"ici apres "<<roots.size();
			roots.push_back(&tree.back());
			rs=roots.size();
			//testt+=2; //test
		}
		//root=(struct node *) malloc(sizeof(struct node));
		root=roots[0];
		std::cout<<"bin "<<tree[5].left.bin<<std::endl;
std::cout<<std::endl;
std::cout<<"root "<<root->freq;


	}

	void display(){

		/*for (size_t i=0;tree.size();i++){
			std::cout<<"leaf : "<<tree[i].leaf<<" freq : "<<tree[i].freq
			<<" root arc["<<tree[i].root.bin<<" "<<tree[i].root.father->freq<<"] "
			<<" left arc["<<tree[i].left.bin<<" "<<tree[i].left.child->freq<<"] "
			<<" right arc["<<tree[i].right.bin<<" "<<tree[i].right.child->freq<<"] "<<std::endl;
		}*/
		size_t i=0;
		struct node * ptr;
		//(ptr->left.child)->leaf
		ptr=&(tree[5]);
		char a=(ptr->left.child)->leaf;
		for(size_t i=4;i<tree.size();i++){
			std::cout<<"| "<<(tree[i].left.child)->leaf<<" |";
		}
		//ptr=tree

		/*while(i<4){
			std::cout<<tree[i].leaf<<" bin "<<(tree[i].root)->bin<<" father "<<tree[i].root.father->freq<<std::endl;
			i++;
		}*/
		if(root->leaf==NULL){
			std::cout<<"TRUE";
		}
		



	}


	std::vector<struct codage>get_code(){
		std::cout<<"ici ";
		std::vector<struct codage> code;
		

		struct node * ptr;
		size_t test=1;
		std::string binc;
		
		while(code.size()!=nb_leaf){
			ptr=root;
			
			//size_t a=((ptr->left).child)->pass;
			
			signed long long a=tree[0].freq;
			
			test=1;
			binc="";
			while(test){
				if((ptr->left.child)->pass!=1){
					if((ptr->left.child)->leaf!=NULL){
						(ptr->left.child)->pass==1;
						struct codage cd;
						cd.bin=binc;
						cd.leaf=(ptr->left.child)->leaf;
						code.push_back(cd);
						test=0;
					}
					else{
						binc.push_back(ptr->left.bin);
						ptr=ptr->left.child;
					}
				}
				else{
					if((ptr->right.child)->pass!=1){
						if((ptr->right.child)->leaf!=NULL){
							(ptr->right.child)->pass==1;
							struct codage cd;
							cd.bin=binc;
							cd.leaf=(ptr->right.child)->leaf;
							code.push_back(cd);
							test=0;
						}
						else{
							binc.push_back(ptr->right.bin);
							ptr=ptr->right.child;
						}
					}
					else{
						ptr->pass=1;
						test=0;
					}
				}

			}



		}

		return code;

	} 




}; 


int main(){
	/*std::string test="abcabbbbcaadeeeeeeeeee";
	std::vector<char> p = probability(test);
	for(size_t i=0;i<p.size();i++){
		std::cout<<p[i]<<" ";
	}
	std::cout<<std::endl;
	std::cout<<"merge sort"<<std::endl;
	struct proba testm;
	testm.ch.push_back('d');
	testm.nb.push_back(4);
	testm.ch.push_back('a');
	testm.nb.push_back(1);
	testm.ch.push_back('c');
	testm.nb.push_back(3);
	testm.ch.push_back('b');
	testm.nb.push_back(2);
	for(size_t i=0;i<4;i++){
		std::cout<<testm.ch[i]<<std::endl;
		std::cout<<testm.nb[i]<<std::endl;
	}
	struct proba res=sort(testm);
	for(size_t i=0;i<4;i++){
		std::cout<<res.ch[i]<<std::endl;
		std::cout<<res.nb[i]<<std::endl;
	}*/
	//std::cout<<"ici"<<std::endl;
	HuffmanTree tr("abcdaabcaabbbaaaaabbbbccccccdddddd");
	/*HuffmanTree * tr=(HuffmanTree *) malloc(sizeof(HuffmanTree));
	*tr=HuffmanTree("abcdaabcaabbbaaaaa");*/
	tr.display();
	//std::vector<struct codage> cod=tr.get_code();



}
