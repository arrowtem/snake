// OOPsnake.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <queue>
#include <conio.h>
#define WIDTH 20
#define HEIGHT 20
#include <stdlib.h> // нужен для вызова функций rand(), srand()
#include <time.h> // нужен для вызова функции time()
class Map {
private:
    char map[WIDTH][HEIGHT];
    int x_bounty;
    int y_bounty;
public:
    Map(int x, int y) {
        for (int i = 0; i < WIDTH; i++)
            for (int j = 0; j < HEIGHT; j++)
                map[i][j] = ' ';
        x_bounty = 0;
        y_bounty = 0;
        map[x][y] = '@';
        create_bounty();
        show_map();
    }
   
    void create_bounty() {    
            srand((unsigned int)time(NULL));
            while (x_bounty >= WIDTH || x_bounty <= 0 || y_bounty >= WIDTH || y_bounty <= 0 || map[x_bounty][y_bounty] == '@') {
                x_bounty = rand() % WIDTH + 1;
                y_bounty = rand() % HEIGHT + 1;
            }
            map[x_bounty][y_bounty] = 'B';
    }

    void show_map() {
        system("cls");
      /*  std::cout << ' ';
        for (int i = 0; i < WIDTH; i++)
            std::cout << '_';
        std::cout << '\n';*/
        for (int i = 0; i < WIDTH; i++)
        {
            /*std::cout << '|';*/
            for (int j = 0; j < HEIGHT; j++)
                std::cout << map[j][i];
            std::cout  << '\n';

        }
      
       
    }
    bool checkBounty(int x, int y) {
        return x == x_bounty && y == y_bounty;
    }
    void set_coord(int x, int y, char symbol) {
        map[x][y] = symbol;
    }
    char returnSymbolAt(int x, int y)
    {
        return map[x][y];
    }
    
};
class Snake {
private:
    std::queue <int> x_loc;
    std::queue <int> y_loc;
    int score;
    int size;

public:
    Snake() {
        x_loc.push(15);
        y_loc.push(15);
        size = 0;
        score = -1;
    }
    int returnFirstX() {
        return x_loc.front();
    }
    int returnFirstY() {
        return y_loc.front();
    }

    bool moveRight(Map& map) {
        x_loc.push(x_loc.back() + 1);
        y_loc.push(y_loc.back());
        if (map.checkBounty(x_loc.back() , y_loc.back()))
        {
            score++;
           
            map.set_coord(x_loc.back(), y_loc.back(), '@');
            map.set_coord(x_loc.back() - 1 , y_loc.back(), '@');
            map.create_bounty();
        }
        else if (map.returnSymbolAt(x_loc.back(),y_loc.back()) == '@'   && x_loc.front()!= x_loc.back() && y_loc.front() != y_loc.back()) {
            return false;
        }
        
        else
        {
            map.set_coord(x_loc.front(), y_loc.front(), ' ');
            map.set_coord(x_loc.back(), y_loc.back(), '@');
            x_loc.pop();
            y_loc.pop();
        }
        return true;
    }
    bool moveLeft(Map& map) {
        x_loc.push(x_loc.back() -1 );
        y_loc.push(y_loc.back());
        if (map.checkBounty(x_loc.back(), y_loc.back()))
        {
            score++;
            
            map.set_coord(x_loc.back(), y_loc.back(), '@');
            map.set_coord(x_loc.back() + 1, y_loc.back() , '@');
            map.create_bounty();
        }
        else if (map.returnSymbolAt(x_loc.back(), y_loc.back()) == '@' && x_loc.front() != x_loc.back() && y_loc.front() != y_loc.back()) {
            return false;
        }
        else
        {
            map.set_coord(x_loc.front(), y_loc.front(), ' ');
            map.set_coord(x_loc.back(), y_loc.back(), '@');
            x_loc.pop();
            y_loc.pop();
        }
        return true;
    }
    bool moveUp(Map& map) {
        x_loc.push(x_loc.back());
        y_loc.push(y_loc.back() - 1);
        if (map.checkBounty(x_loc.back(), y_loc.back()))
        {
            score++;
            
            map.set_coord(x_loc.back(), y_loc.back() , '@');
            map.set_coord(x_loc.back(), y_loc.back() + 1, '@');
            map.create_bounty();
            
        }
        else if (map.returnSymbolAt(x_loc.back(), y_loc.back()) == '@' && x_loc.front() != x_loc.back() && y_loc.front() != y_loc.back()) {
            return false;
        }
        else
        {
            map.set_coord(x_loc.back(), y_loc.back(), '@');
            map.set_coord(x_loc.front(), y_loc.front(), ' ');
            x_loc.pop();
            y_loc.pop();
        }
        return true;
    }
    bool moveDown(Map& map) {
        x_loc.push(x_loc.back());
        y_loc.push(y_loc.back() + 1);
        if (map.checkBounty(x_loc.back(), y_loc.back()))
        {
            
            score++;
            map.set_coord(x_loc.back(), y_loc.back(), '@');
            map.set_coord(x_loc.back(), y_loc.back() - 1, '@');
            map.create_bounty();
        }
        else if (map.returnSymbolAt(x_loc.back(), y_loc.back()) == '@' && x_loc.front() != x_loc.back() && y_loc.front() != y_loc.back()) {
            return false;
        }
        else
        {
            map.set_coord(x_loc.back(), y_loc.back(), '@');
            map.set_coord(x_loc.front(), y_loc.front(), ' ');
            x_loc.pop();
            y_loc.pop();
        }
        return true;

    }
};

int main()
{
    Snake snake;
    Map map(snake.returnFirstX(),snake.returnFirstY());
    char ch,prev_ch;
    ch = 'g';
    bool state = true;
    do {
        prev_ch = ch;
        ch = _getch();
        if (prev_ch == 'a' && ch == 'd' || prev_ch == 'd' && ch == 'a' || prev_ch == 'w' && ch == 's' || prev_ch == 's' && ch == 'w' )
            continue;
        switch (ch) {
        case 'w':
            state = snake.moveUp(map);
            break;
        case 's':
            state =  snake.moveDown(map);
            break;
        case 'a':
            state =  snake.moveLeft(map);
            break;
        case 'd':
            state =  snake.moveRight(map);
            break;
        default:
            break;
        }
        if (!state)
            break;
        map.show_map();
    } while (ch != '.');
    system("cls");
    std::cout << "you loose ";
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
