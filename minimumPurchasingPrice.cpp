#include <iostream>
#include <vector>

using namespace std;

int CalDiscount(vector<vector<string> > discounts, string price, string discount);
int CalPrice(vector<vector<string> > products, vector<vector<string> > discounts);

int CalPrice(vector<vector<string> > products, vector<vector<string> > discounts){
    int TotalPrice = 0;
    int DiscountPrice = 0;
    int TempDiscountPrice = 0;
    //Check if there is no products defined, Ignore case
    if(products.size()==0){
        return 0;
    }
    //Check if no discounts offered, return the original product price
    if(discounts.size()==0 && products.size()!=0){
        for(vector<string> price : products){
            TotalPrice+=stoi(price[0]);
        }
    }
    else{
        for(vector<string> product:products){
            DiscountPrice = stoi(product[0]);
            if(product.size()==1){ //no discounts
               TotalPrice+=stoi(product[0]); 
            }
            else{
                for(int i=1; i<product.size(); i++){
                    //Calculate discounted price based on discount tag
                    TempDiscountPrice = CalDiscount(discounts, product[0], product[i]);
                    if (TempDiscountPrice < DiscountPrice){
                        DiscountPrice = TempDiscountPrice;
                    }
                }
                TotalPrice+=DiscountPrice;
            }
        }
    }
    return TotalPrice;
}

int CalDiscount(vector<vector<string> > discounts, string price, string discount_tag){
    int dis_price=stoi(price);
    for(vector<string> discount:discounts){
        if(discount[0]==discount_tag){
            if(discount[1]=="0"){
                dis_price = stoi(price);
            }
            else if(discount[1]=="1"){
                dis_price = stoi(price) - (0.01 * stoi(price) * stoi(discount[2]));
            }
            else if(discount[1]=="2"){
                dis_price = stoi(price) - stoi(discount[2]);
            }
            else{
                cout << "Invalid discount type:" <<discount[1]<<endl;
                cout << "No discount added to original price" <<endl;
                dis_price = stoi(price);
            }
        }
    }
    return dis_price;
}
int main()
{
    int final_price = 0;
    vector<vector<string> > products= {
        {"100", "d1", "d2"},
        {"10"},
        {"17","d2"},
        {"100", "d3"},
        {"200" , "None"},
        {"10", "d0"},
        {"10", "d0", "d4"}
    };
    vector<vector<string> > discounts={
        {"d0" ,"0"},
        {"d1", "1", "10"},
        {"d2", "2", "5"},
        {"d3", "1", "20"},
        {"d4", "2", "5"}
    };
    
    final_price = CalPrice(products, discounts);
    cout << "Final Product's Best Price : "<< final_price<<endl;
    return 0;
}
