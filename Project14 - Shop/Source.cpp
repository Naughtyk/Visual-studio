#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

class Product
{
	static int nextcode;
	string name;
	size_t code;
	size_t price = 0;
	size_t count = 0;
public:
	Product(string name) : name(name) { code = nextcode++; }
	void Get(size_t count)
	{
		this->count -= count;
	}
	size_t GetPrice()
	{
		return this->price;
	}
	size_t GetSumPrice(size_t count)
	{
		return count * this->price;
	}
	size_t GetCount()
	{
		return this->count;
	}
	string GetName()
	{
		return this->name;
	}
	size_t GetCode()
	{
		return this->code;
	}
	void Load(size_t count, size_t price)
	{
		this->price = price;
		this->count = count;
	}
};

class Shop
{
	static int nextcode;
	size_t code = 0;
	string name;
	string address;
	unordered_map<size_t, Product> products;
public:
	Shop(string name, string address) :name(name), address(address) { code = nextcode++; }
	void AddProducts(Product prod, size_t count, size_t price)
	{
		products.insert({ prod.GetCode(), prod });
		products.find(prod.GetCode())->second.Load(count, price);
	}
	size_t isInstance(size_t code)
	{
		if (products.count(code) == 0)
			return 0;
		return 1;
	}
	size_t GetPrice(size_t code)
	{
		return products.find(code)->second.GetPrice();
	}
	string GetName()
	{
		return this->name;
	}
	size_t GetCode()
	{
		return this->code;
	}
	vector<pair<string, size_t>> Buy(size_t money)
	{
		size_t sum = 0;
		vector<pair<string, size_t>> result = vector<pair<string, size_t>>();
		for (auto item = products.begin(); item != products.end(); item++)
		{
			if (sum < money)
			{
				if (item->second.GetCount() > 0)
				{
					size_t x = (money - sum) / item->second.GetPrice();
					if (x > item->second.GetCount())
						x = item->second.GetCount();
					sum += x * item->second.GetPrice();
					if (x > 0)
						result.push_back(make_pair(item->second.GetName(), x));
				}
			}
			else break;
		}
		return result;
	}
	int BuyVector(vector<size_t> codes, vector<size_t> counts)
	{
		for (size_t i = 0; i < codes.size(); i++)
		{
			size_t count = products.find(codes[i])->second.GetCount();
			if (count < counts[i])
			{
				return -1;
			}
		}
		size_t sum = 0;
		for (size_t i = 0; i < codes.size(); i++)
		{
			size_t count = products.find(codes[i])->second.GetCount();
			sum += products.find(codes[i])->second.GetSumPrice(counts[i]);
			products.find(codes[i])->second.Get(count);
		}
		return sum;
	}
	int GetPriceOnVector(vector<size_t> codes, vector<size_t> counts)
	{
		for (size_t i = 0; i < codes.size(); i++)
		{
			if (products.count(codes[i]) == 0)
			{
				return -1;
			}
			size_t count = 0;
			count = products.find(codes[i])->second.GetCount();
			if (count < counts[i])
			{
				return -1;
			}
		}

		size_t sum = 0;
		for (size_t i = 0; i < codes.size(); i++)
		{
			size_t count = products.find(codes[i])->second.GetCount();
			sum += products.find(codes[i])->second.GetSumPrice(count);
		}
		return sum;
	}
};

class ShopManager
{
	vector<Shop> shops;
	vector<Product> products;
public:
	ShopManager() {}
	void AddShop(Shop shop)
	{
		shops.push_back(shop);
	}
	void AddProduct(Product product)
	{
		products.push_back(product);
	}
	vector<Shop> &GetShops() {
		return this->shops;
	}
	vector<Product> &GetProducts() {
		return this->products;
	}
	void createshop(string str1, string str2) {
		Shop shop = Shop(str1, str2);
		AddShop(shop);
	}
	void createproduct(string str) {
		Product product = Product(str);
		AddProduct(product);
	}
};

int Product::nextcode = 0;
int Shop::nextcode = 0;

string ShopSellsCheapestProduct(size_t code, vector<Shop> v_shops)
{
	vector<Shop>::iterator item = v_shops.begin();
	size_t minimumPrice = item->GetPrice(code);
	string NameShop = item->GetName();
	for (; item != v_shops.end(); item++)
	{
		if (item->isInstance(code) == 0)
			continue;
		if (item->GetPrice(code) < minimumPrice)
		{
			minimumPrice = item->GetPrice(code);
			NameShop = item->GetName();
		}
	}
	return NameShop;
}

string ShopSellsCheapestVector(vector<size_t> codes, vector<size_t> counts, vector<Shop> v_shops)
{
	size_t sum = 0;
	string nameShop;
	for (auto item = v_shops.begin(); item != v_shops.end(); item++)
	{
		size_t shopSum = item->GetPriceOnVector(codes, counts);
		if (shopSum == -1)
			continue;
		if (sum == 0)
		{
			sum = shopSum;
			nameShop = item->GetName();
			continue;
		}
		if (sum > shopSum)
		{
			sum = shopSum;
			nameShop = item->GetName();
		}
	}
	return nameShop;
}

int main()
{
	ShopManager shopmanager;
	shopmanager.createshop("Okei", "Lenina, 1");
	shopmanager.createshop("Dikci", "Lenina, 2");
	shopmanager.createshop("Lenta", "Lenina, 3");
	shopmanager.createproduct("Tomato");
	shopmanager.createproduct("Potato");
	shopmanager.createproduct("Carrot");
	shopmanager.createproduct("Onion");
	shopmanager.createproduct("Apple");
	shopmanager.createproduct("Fish");
	shopmanager.createproduct("Beef");
	shopmanager.createproduct("Chicken");
	shopmanager.createproduct("Milk");
	shopmanager.createproduct("Cheese");
	shopmanager.GetShops()[0].AddProducts(shopmanager.GetProducts()[0], 100, 10);
	shopmanager.GetShops()[0].AddProducts(shopmanager.GetProducts()[1], 150, 20);
	shopmanager.GetShops()[0].AddProducts(shopmanager.GetProducts()[2], 50, 15);
	shopmanager.GetShops()[0].AddProducts(shopmanager.GetProducts()[3], 40, 50);
	shopmanager.GetShops()[0].AddProducts(shopmanager.GetProducts()[4], 20, 30);
	shopmanager.GetShops()[0].AddProducts(shopmanager.GetProducts()[5], 5, 200);

	shopmanager.GetShops()[1].AddProducts(shopmanager.GetProducts()[0], 100, 10);;
	shopmanager.GetShops()[1].AddProducts(shopmanager.GetProducts()[1], 150, 20);
	shopmanager.GetShops()[1].AddProducts(shopmanager.GetProducts()[3], 50, 15);
	shopmanager.GetShops()[1].AddProducts(shopmanager.GetProducts()[4], 40, 50);
	shopmanager.GetShops()[1].AddProducts(shopmanager.GetProducts()[8], 20, 30);
	shopmanager.GetShops()[1].AddProducts(shopmanager.GetProducts()[9], 5, 200);

	shopmanager.GetShops()[2].AddProducts(shopmanager.GetProducts()[0], 100, 10);;
	shopmanager.GetShops()[2].AddProducts(shopmanager.GetProducts()[1], 150, 20);
	shopmanager.GetShops()[2].AddProducts(shopmanager.GetProducts()[2], 50, 15);
	shopmanager.GetShops()[2].AddProducts(shopmanager.GetProducts()[6], 40, 50);
	shopmanager.GetShops()[2].AddProducts(shopmanager.GetProducts()[7], 20, 30);
	shopmanager.GetShops()[2].AddProducts(shopmanager.GetProducts()[8], 5, 200);

	cout << "============================" << endl;
	cout << "The shop sells the cheapest tomato: ";
	cout << ShopSellsCheapestProduct(3, shopmanager.GetShops()) << endl;
	cout << "The shop sells the cheapest carrot: ";
	cout << ShopSellsCheapestProduct(4, shopmanager.GetShops()) << endl;
	cout << "============================" << endl;
	cout << "500 rub can buy anything at Okei: " << endl;
	vector<pair<string, size_t>> Ibuy = shopmanager.GetShops()[0].Buy(500);
	for (auto item = Ibuy.begin(); item != Ibuy.end(); item++)
	{
		cout << item->first << ": " << item->second << endl;
	}
	cout << "============================" << endl;
	cout << "Buy 5 onions and 3 apples at Okei: ";
	cout << shopmanager.GetShops()[0].BuyVector({ 3, 4 }, { 5, 3 }) << endl;
	cout << "Buy 7 beef and 11 chicken at Lenta: ";
	cout << shopmanager.GetShops()[2].BuyVector({ 6, 7 }, { 7, 11 }) << endl;
	cout << "============================" << endl;
	cout << "The shop sells the cheapest 3 tomatoes and 2 potatoes: ";
	cout << ShopSellsCheapestVector({ 0, 1 }, { 3, 2 }, shopmanager.GetShops()) << endl;

	return 0;
}