/*
    briot ruffini
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<double> briot_ruffini(double root, vector<double> &pol){
    double result = pol[0];
    vector<double> newPol = {pol[0]};

    for (int i = 0; i < pol.size()-1; ++i){
        result *= root;
        result += pol[i+1];

        newPol.push_back(result);
    }

    if(result==0){
        return newPol;
    }else {
        newPol.clear();
        return newPol;
    }
}

bool already_exists(double num, vector<double> &v){
    vector<double>::iterator it;
    it = find(v.begin(), v.end(), num);

    if(it==v.end()){
        return 0;
    }else {
        return 1;
    }
}

void generate_roots(vector<double> &pol, vector<double> &roots){
    if(*(--pol.end()) != 0){
        double a0 = *(--pol.end());
        double an = *(pol.begin());

        vector<double> p;
        for (double i = abs(a0); i > 0; --i){
            if(fmod(a0, i) == 0){
                p.push_back(i);
                p.push_back(i*-1);
            }
        }

        vector<double> q;
        for (double i = abs(an); i > 0; --i){
            if(fmod(an, i) == 0){
                q.push_back(i);
                q.push_back(i*-1);
            }
        }

        for (int i = 0; i < p.size(); ++i){
            for (int j = 0; j < q.size(); ++j){
                if(!already_exists((p[i]/q[j]), roots)){
                    roots.push_back(p[i]/q[j]);
                }
            }
        }
    }
}

int main(int argc, char **argv){

    cout << "=========================================================" << endl;
    cout << "=                                                       =" << endl;
    cout << "=                     Briot Ruffini                     =" << endl;
    cout << "=                                                       =" << endl;
    cout << "=========================================================" << endl << endl;

    int n;
    int cRoots = 0;

    cout << "Enter the number of polynomial coefficients: ";
    cin >> n;
    cout << endl;

    vector<double> pol;
    vector<double> roots = {0};

    for (int i = n; i >= 0; i--) {
        float a;
        cout << "Enter the value of the degree coefficient " << i << ":";
        cin >> a;
        pol.push_back(a);
    }  

    generate_roots(pol, roots);

    cout << endl;
    for (int i = 0; i < roots.size(); ++i){
        vector<double> newPol = briot_ruffini(roots[i], pol);

        if(!newPol.empty()){
            cRoots++;
            cout << roots[i] << " it's root!" << endl;

            int n2 = n;
            cout << "The new polynomial is: ";
            for (int j = 0; j < newPol.size()-1; ++j){
                n2--;

                if(j==newPol.size()-2){
                    cout << newPol[j] << "x^" << n2;
                }else {
                    cout << newPol[j] << "x^" << n2 << " + ";
                }
            }

            cout << endl;
        }
        
        newPol.clear();
    }

    if(cRoots == 0){
        cout << "the polynomial has no rational roots!" << endl;
    }

    
    return 0;
}