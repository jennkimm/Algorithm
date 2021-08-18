#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <assert.h>
#define ll long long
#define lui long unsigned int
#define mod 1000000007

using namespace std;

struct Pizza{
	ll id; // 피자 index
	ll tn; // 토핑 갯수
	vector<ll> ingredients; // ingredients 상의 재료 index로 저장.
};

struct Group{
	lui size;
	vector<ll> pizzas;
	vector<ll> ingredients;
	lui score;
};

ll inter(vector<ll> &s1, vector<ll> &s2){
    vector<ll> s3;
    set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(), back_inserter(s3)); // 교집합 구하기
    return s3.size(); // 겹치는 재료의 갯수
};

void print_s(vector<ll> pizzas){
    cout << pizzas.size() << " ";
    for(lui i=0; i<pizzas.size(); ++i){
        if(i == pizzas.size()-1){
            cout << pizzas[i] << "\n";
            return;
        }
        cout << pizzas[i] << " ";
    }
}

lui score_d(vector<Group> groups, Group group) {
    if(group.pizzas.size() != groups.size())
		return 0;
    return group.ingredients.size() * group.ingredients.size();
}


int main(){
	ll M, T2, T3, T4;
	cin >> M >> T2 >> T3 >> T4;

	unordered_map<string, ll> ingredients;
	vector<Pizza> pizzas;
	vector<Group> groups;

	for(ll i = 0; i < M; i++) {
		Pizza p;
		p.id = i;
		cin >> p.tn;
		for (ll j = 0; j < p.tn; j++) {
			string ingredient;
			cin >> ingredient;
			if (ingredients.count(ingredient) == 0) { // ingredients 사전에 추가
				ingredients[ingredient] = ingredients.size();
			}
			p.ingredients.push_back(ingredients[ingredient]);
		}
		sort(p.ingredients.begin(), p.ingredients.end());
		pizzas.push_back(p);
	}

	sort(pizzas.begin(), pizzas.end(), [](const Pizza& p1, const Pizza& p2){
        return p1.ingredients.size() < p2.ingredients.size(); // 재료순 내림차순 정렬
    });

	for (ll i = 0; i < T4; i++) {
		Group group;
		group.size = 4;
		groups.push_back(group);
	}

	for (ll i = T4; i < T4 + T3; i++) {
		Group group;
		group.size = 3;
		groups.push_back(group);
	}

	for (ll i = T4 + T3; i < T4 + T2 + T3; i++) {
		Group group;
		group.size = 2;
		groups.push_back(group);
	}

	while(M>0 && (T2>0 || T3>0 || T4>0)) {
		ll group_index = -1, m_g = 0;
		for (lui i = 0; i < groups.size(); i++){
			if(groups[i].pizzas.size() != groups[i].size){ // 아직 이 그룹에 피자가 더 필요하다면
                if (group_index == -1) {
					group_index = i;
					m_g = inter(pizzas[M-1].ingredients, groups[i].ingredients);
                    continue;
				}
				if (inter(pizzas[M-1].ingredients, groups[i].ingredients) < m_g) {
                    group_index = i;
                    m_g = inter(pizzas[M-1].ingredients, groups[i].ingredients);
                }
			}
		}

		if(group_index == -1)
			break;

		//groups[group_index].add_pizza(pizzas[M-1]);
		// group_index 번째 그룹에 pi
		groups[group_index].pizzas.push_back(pizzas[M-1].id);
		vector<ll> s3;
		set_union(pizzas[M-1].ingredients.begin(), pizzas[M-1].ingredients.end(), groups[group_index].ingredients.begin(), groups[group_index].ingredients.end(), back_inserter(s3));
		groups[group_index].ingredients = s3;
		if(groups[group_index].pizzas.size()==groups[group_index].size){
            if(groups[group_index].size == 2) T2--;
            if(groups[group_index].size == 3) T3--;
            if(groups[group_index].size == 4) T4--;
        }
        M--;
	}

	// output
    ll aux=0;
    for(lui i=0; i<groups.size(); ++i){
        if(groups[i].pizzas.size()==groups[i].size){
            aux++;
        }
    }
    cout << aux << "\n";

	lui score=0;

    for(lui i=0; i<groups.size(); ++i){
        if(groups[i].pizzas.size()==groups[i].size){
            print_s(groups[i].pizzas);
            groups[i].score = groups[i].score + score_d(groups, groups[i]);
        }
    }
    cout << score << "\n";
    return 0;
}
