#include <iostream>
#include <vector>
#include <stdexcept>
#include <exception>


using namespace std;

class Pizza
{
private:

    string name;
    string description;
    int size;
    int salt = 0;
    int price = 0;
    int cheesed = 0;
    unsigned int pfs; // коэфициент наценки на пиццу
    Pizza(string name, string description,unsigned int pfs)
    {
        this->name = move(name);
        this->description = move(description);
        this->pfs = pfs;
    }
protected:
    Pizza() = default;
public:
    int AvailSize[4] = {50, 70, 90, 110};
    static const vector<string> pizzas;


    static Pizza Mexico()
    {
        return Pizza(pizzas[0], "Мясной фарш, перец сладкий, кукуруза, лук, свежие томаты, перец красный молотый, сыр Моцарелла, томатный соус", 6);
    }
    static Pizza Veget()
    {
        return Pizza(pizzas[1], "Шампиньоны, свежие томаты, перец сладкий, брокколи, сыр Моцарелла, томатный соус", 7);
    }
    static Pizza Peperony()
    {
        return Pizza(pizzas[2], "Соус томатный, бекон домашний, фарш говяжий, лук, перец сладкий, лук, томаты, острый соус, сыр моцарелла", 4);
    }
    static Pizza Virginia()
    {
        return Pizza(pizzas[3], "Соус томатный, острый соус, сыр моцарелла, колбаски охотничьи, перец болгарский, кукуруза, томаты, бекон.", 6);
    }
    int GetPrice()
    {
        return price;
    }

    virtual void getListOfPizzas() {};
    virtual void getListOfSizes() {};

    virtual void addSalt (int temp)
    {
        if (temp <= 0)
            throw logic_error("Нельзя попросить посолить и не дать соль!");
        if (temp > 100)
            throw logic_error("Так пересолили, что есть невозможно!");
        salt = salt + temp;
        price = price + temp/10;
    }
    virtual void addCheese (int temp)
    {
        if (temp <= 0)
            throw logic_error("Нельзя попросить посолить и не дать соль!");
        if (temp > 100)
            throw logic_error("Так пересолили, что есть невозможно!");
        cheesed = cheesed + temp;
        price = price + temp * 2;
    }
    virtual void setSize (int temp)
    {
        if (temp > 4 || temp < 0)
            throw logic_error("У нас таких размеров пиццы нет!");
        size = AvailSize[temp];
        price = price + AvailSize[temp] * pfs;
    }
    virtual void PrintPizza()
    {
        cout <<"Название пиццы: " << name << endl;
        cout <<"Описание: " << description << endl;
        cout <<"Размер: " << size << endl;
        cout << "Соль: " << salt << " Сыр: " << cheesed << endl;
    }
};

const vector<string> Pizza::pizzas = {"Мексиканская", "Вегетарианская", "Пеперони", "Верджиния"};


class Order: public Pizza{
private:
    vector<Pizza> order;
public:
    Order() =  default;

    void Welcome()
    {
        cout << "----------------------------------------------------------------------" << endl;
        cout << "---------------Добро пожаловать в пиццерию у Скурихина----------------" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        cout << "--Только сегодня, при заказе 3 пиц, троечка по коллоквиуму в подарок--" << endl;
        cout << "----------------------------------------------------------------------" << endl;

    }
    void PrintPizza() override
    {
        int finalPrice = 0;
        cout << "--------------------Заказ-------------------------------" << endl;
        for (int i = 0; i < order.size(); i++)
        {
            cout << "#" <<i + 1 << "  ";
            order[i].PrintPizza();
            cout << "--------------------------------------------------------" << endl;

            finalPrice += order[i].GetPrice();
        }
        cout << "---------- Итоговая стоимость заказа равна " << finalPrice << " руб.-----" << endl;
    }

    void setSize(int temp) override
    {
        if (!order.empty())
            order.back().setSize(temp);
        else
            throw logic_error("Вы еще ничего не заказали!");
    }

    void addSalt(int temp) override
    {
        order.back().addSalt(temp);
    }

    void addCheese(int temp) override
    {
        order.back().addCheese(temp);
    }

    void getListOfPizzas() override
    {
        cout << "Ассортимент: " << endl;
        for (int i = 0; i < pizzas.size(); i++)
            cout << i + 1 << ": " << pizzas[i] << endl;
    }
    void getListOfSizes() override
    {
        cout << "Все доступные размеры пиццы: " << endl;
        for (int i = 0; i < 4; i ++)
        {
            cout << i + 1 << ": " << AvailSize[i] << endl;
        }
    }

    void addToOrder(int temp)
    {
        if (temp < 1 || temp > pizzas.size())
            throw logic_error("У нас нет такого номера пиццы!");

        switch (temp)
        {
            case 1:
                order.push_back(Pizza::Mexico());
                break;
            case 2:
                order.push_back(Pizza::Veget());
                break;
            case 3:
                order.push_back(Pizza::Peperony());
                break;
            case 4:
                order.push_back(Pizza::Virginia());
                break;
        }
    }


};

void StartOrder()
{
    Order ord;
    bool Continue = true;

    ord.Welcome();

    do
    {
      ord.getListOfPizzas();
      do {
          cout << "Выберите номер пиццы в меню" << endl;
          int count;
          cin >> count;
          if (count <= 4 && count >= 1)
          {
              ord.addToOrder(count);
              Continue = false;
          }
          else
          {
              cout << "Такой пиццы нет в нашем меню, попробуйте еще раз" << endl;
              Continue = true;
          }
      }while (Continue);
        do {
            cout << "Выберите размер пиццы: " << endl;
            ord.getListOfSizes();
            int count;
            cin >> count;
            if (count <= 4 && count >= 1)
            {
                ord.setSize(count - 1);
                Continue = false;
            }
            else
            {
                cout << "Такого размера пиццы у нас нет! " << endl;
                Continue = true;
            }
        } while(Continue);
        string wants;
        cout << "Добавить соль? <yes/no>" << endl;
        cin >> wants;
        if (wants == "yes")
        {
            do{
                cout << "Сколько соли добавить?" << endl;
                int count;
                cin >> count;
                if (count > 0 && count <= 100)
                {
                    ord.addSalt(count);
                    Continue = false;
                }
                else
                {
                    cout << "Нельзя добавить столько соли!" << endl;
                    Continue = true;
                }
            } while (Continue);
        }

        cout << "Добавить сыр? <yes/no>" << endl;
        cin >> wants;
        if (wants == "yes")
        {
            do{
                cout << "Сколько сыра добавить?" << endl;
                int count;
                cin >> count;
                if (count > 0 && count <= 100)
                {
                    ord.addCheese(count);
                    Continue = false;
                }
                else
                {
                    cout << "Нельзя добавить столько сыра!" << endl;
                    Continue = true;
                }
            } while (Continue);
        }

      cout << "Может ещё одну пиццу для Вас и ваших друзей? <yes/no>" << endl;
      string repeat;
      cin >> repeat;
      if (repeat == "yes")
      {
          Continue = true;
      }
      else
      {
          if (repeat == "no")
              Continue = false;
          else
          {
              Continue = false;
              cout << " Ви донт спик чайниз!" << endl;
          }

      }

    } while (Continue);
    ord.PrintPizza();
}

