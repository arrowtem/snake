#include <iostream>
#include <queue>
#include <conio.h>
#define WIDTH 22
#define HEIGHT 22
#include <stdlib.h> // нужен для вызова функций rand(), srand()
#include <time.h> // нужен для вызова функции time()
#include <windows.h>
class Map {
private:
    char map[WIDTH][HEIGHT];
    int x_bounty;
    int y_bounty;
public:
    Map(int x, int y) {
        for (int i = 1; i < WIDTH-1; i++)
            for (int j = 1; j < HEIGHT-1; j++)
                map[i][j] = ' ';
        for (int i = 0; i < WIDTH ; i++)
            for (int j = 0; j < HEIGHT ; j++)
                if (map[i][j] != ' ')
                    map[i][j] = 'X';
        x_bounty = 0;
        y_bounty = 0;
        map[x][y] = '@';
        create_bounty();
        show_map();
    }

    void create_bounty() {
        srand((unsigned int)time(NULL));
        while (x_bounty > WIDTH  || x_bounty < 1 || y_bounty > HEIGHT - 1|| y_bounty < 1 || map[x_bounty][y_bounty] == '@' || map[x_bounty][y_bounty] == 'X') {
            x_bounty = rand() % (WIDTH - 1) + 1;
            y_bounty = rand() % (HEIGHT - 1) + 1;
        }
        map[x_bounty][y_bounty] = 'B';
    }

    void show_map() {
        std::cout << "\33[2J\33[H";
        for (int i = 0; i < WIDTH; i++)
        {
            
            for (int j = 0; j < HEIGHT; j++)
                std::cout << map[j][i];
            std::cout << '\n';

        }
        std::cout << ' ';
        
            

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
    int speed;

public:
    Snake() {
        x_loc.push(15);
        y_loc.push(15);
        size = 0;
        score = -1;
        speed = 200;
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
        if (map.checkBounty(x_loc.back(), y_loc.back()))
        {
            score++;
            speed -= 20;

            map.set_coord(x_loc.back(), y_loc.back(), '@');
            map.set_coord(x_loc.back() - 1, y_loc.back(), '@');
            map.create_bounty();
        }
        else if (map.returnSymbolAt(x_loc.back(), y_loc.back()) == '@'|| map.returnSymbolAt(x_loc.back(), y_loc.back()) == 'X'){
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
    int returnSpeed() {
        return speed;
    }
    bool moveLeft(Map& map) {
        x_loc.push(x_loc.back() - 1);
        y_loc.push(y_loc.back());
        if (map.checkBounty(x_loc.back(), y_loc.back()))
        {
            score++;
            speed -= 20;
            map.set_coord(x_loc.back(), y_loc.back(), '@');
            map.set_coord(x_loc.back() + 1, y_loc.back(), '@');
            map.create_bounty();
        }
        else if (map.returnSymbolAt(x_loc.back(), y_loc.back()) == '@' || map.returnSymbolAt(x_loc.back(), y_loc.back()) == 'X') {
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
            speed -= 20;
            map.set_coord(x_loc.back(), y_loc.back(), '@');
            map.set_coord(x_loc.back(), y_loc.back() + 1, '@');
            map.create_bounty();

        }
        else if (map.returnSymbolAt(x_loc.back(), y_loc.back()) == '@' || map.returnSymbolAt(x_loc.back(), y_loc.back()) == 'X') {
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
            speed -= 20;
            score++;
            map.set_coord(x_loc.back(), y_loc.back(), '@');
            map.set_coord(x_loc.back(), y_loc.back() - 1, '@');
            map.create_bounty();
        }
        else if (map.returnSymbolAt(x_loc.back(), y_loc.back()) == '@' || map.returnSymbolAt(x_loc.back(), y_loc.back()) == 'X') {
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
    Map map(snake.returnFirstX(), snake.returnFirstY());
    char ch, prev_ch;
    ch = 'g';
   
    bool state = true;
    do {
        prev_ch = ch;
       
        if (prev_ch == 'a' && ch == 'd' || prev_ch == 'd' && ch == 'a' || prev_ch == 'w' && ch == 's' || prev_ch == 's' && ch == 'w')
            continue;
        if(_kbhit()!=0)
            ch = _getch();
        Sleep(snake.returnSpeed());
        switch (prev_ch) {
        case 'w':
            state = snake.moveUp(map);
            break;
        case 's':
            state = snake.moveDown(map);
            break;
        case 'a':
            state = snake.moveLeft(map);
            break;
        case 'd':
            state = snake.moveRight(map);
            break;
        default:
            break;
        }
        if (!state)
            break;
        map.show_map();
    } while (true);
    std::cout << "\33[2J\33[H";
    std::cout << "you loose ";
    return 0;
}