#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void out_vec(vector<int> vec_1)
{
    int n = vec_1.size();
    for(int i = 0; i < n; i++)
    {
        cout << vec_1[i];
    }
    cout << endl;
}

/*Funkce pro převedení obou vektorů na stejnou délku aby se s nima dalo pěkně pracovat*/
vector<int> simv(vector<int> vec_1, vector<int> vec_2)
{
    int s1, s2;
    s1 = vec_1.size();
    s2 = vec_2.size();
    if(s1 > s2)
    {
        vector<int>::iterator it;
        for(int i = s2; i < s1; i++)
        {
            it = vec_2.begin(); // nevím jestli je tohle nejlepší řešení ale funguje
            vec_2.insert(it, 0);
        }
        return vec_2;
    }
    else if(s2 > s1)
    {
        vector<int>::iterator it;
        for(int i = s1; i < s2; i++)
        {
            it = vec_1.begin();
            vec_1.insert(it, 0);
        }
        return vec_1;
    }
}

/*Funkce pro sčítání "pod sebou"*/
void addv(vector<int> vec_1, vector<int> vec_2)
{
    int ast1 = 0, ast2 = 0, ast3 = 0, carry = 0;
    int n = vec_1.size();
    vector<int> res;
    for(int i = n; i > 0; i--)
    {
        ast1 = vec_1[i-1];
        ast2 = vec_2[i-1];
        ast3 = ast1 + ast2 + carry;
        if(ast3 >= 10)
        {
            carry = 1;
            ast3 -= 10;
        }else carry = 0;
        res.push_back(ast3);
    }
    if(carry>0) res.push_back(carry);
    int q = res.size();
    for(int i = q; i > 0; i--) cout << res[i-1];
    cout << endl;
}

/*Funkce pro odčítání "pod sebou"*/
void subv(vector<int> vec_1, vector<int> vec_2)
{
    int ast1 = 0, ast2 = 0, ast3 = 0, carry = 0;
    int n = vec_1.size();
    vector<int> res;
    for(int i = n; i > 0; i--)
    {
        ast1 = vec_1[i-1];
        ast2 = vec_2[i-1];
        if(ast2 > ast1)
        {
            ast1 += 10;
            ast3 = ast1 - (ast2 + carry);
            carry = 1;
        }else
        {
            ast3 = ast1 - (ast2 + carry);
            carry = 0;
        }
        res.push_back(ast3);
    }
    int q = res.size();
    for(int i = q; i > 0; i--) cout << res[i-1];
    cout << endl;
}

int main()
{
    vector<int> vec_1, vec_2;

 /*Připravení dvou vektorů pro testování*/
    vec_1.push_back(6);
    vec_1.push_back(1);
    vec_1.push_back(9);
    vec_1.push_back(3);
    vec_1.push_back(8);
    vec_1.push_back(5);

    vec_2.push_back(5);
    vec_2.push_back(5);
    vec_2.push_back(5);
    vec_2.push_back(3);
 /****************************************/

    out_vec(vec_1);
    out_vec(vec_2); //Vypíšu oba vektory

    if(vec_2.size() < vec_1.size())
    {
        vec_2 = simv(vec_1, vec_2);
    }
    else if(vec_1.size() < vec_2.size()) vec_1 = simv(vec_1, vec_2);

    cout << "------\n";
    addv(vec_1, vec_2); //Sečtu je

    cout << "------\n";
    subv(vec_1, vec_2); //Odečtu je
    //POZNÁMKA: Odčítání nefunguje správně když se odečítá větší číslo od menšího

    return 0;
}
