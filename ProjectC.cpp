#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include "Field.h"
using namespace sf;
using namespace std;
 
void unveal(int smap[][12], Field* map[][12], int a, int b);
const int mapSize=12, w=32;

int main(){
    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");

    int HP = 3;
    Field *grid [mapSize][mapSize];
    int sgrid[mapSize][mapSize]; //for showing

    Texture t;
    t.loadFromFile("images/tiles.jpg");
    Sprite s(t);

    for (int i=0; i<mapSize; i++)
        for (int j=0; j< mapSize; j++)
        {
            sgrid[i][j] = 10;
            if(i==0 || j==0 || i==mapSize-1 || j==mapSize-1) grid[i][j] = new Default();
            else if (rand() % 7 == 0)  grid[i][j] = new Bomb();
            else if (rand() % 13 == 0)  grid[i][j] = new Trap();
            else grid[i][j] = new Default();
        }

    for (int i=1; i<mapSize-1; i++)
        for (int j=1; j<mapSize-1 ;j++)
        {
            int n = 0;
            if (grid[i][j]->fieldType() != 0) continue;
            if (grid[i + 1][j]->fieldType() != 0) n++;
            if (grid[i][j + 1]->fieldType() != 0) n++;
            if (grid[i - 1][j]->fieldType() != 0) n++;
            if (grid[i][j - 1]->fieldType() != 0) n++;
            if (grid[i + 1][j + 1]->fieldType() != 0) n++;
            if (grid[i - 1][j - 1]->fieldType() != 0) n++;
            if (grid[i - 1][j + 1]->fieldType() != 0) n++;
            if (grid[i + 1][j - 1]->fieldType() != 0) n++;
            grid[i][j]->setType(n);
        }

    while (app.isOpen()){
        Vector2i pos = Mouse::getPosition(app);
        int x = pos.x / w;
        int y = pos.y / w;

        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();

            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left) {
                    if (sgrid[x][y] == 10) grid[x][y]->dmg(&HP);
                    sgrid[x][y] = grid[x][y]->getType();
                    
                    if (grid[x][y]->getType() == 0) {
                        unveal(sgrid, grid, x, y);
                    }

                }
                else if (e.key.code == Mouse::Right) {
                    if (sgrid[x][y] == 11) sgrid[x][y] = 10;
                    else sgrid[x][y] = 11;
                }
        }

        app.clear(Color::White);

        for (int i=1; i<mapSize-1; i++)
            for (int j=1; j<mapSize-1; j++)
            {
                if (sgrid[x][y] == 9 || HP==0) sgrid[i][j] = grid[i][j]->getType();
                s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w));
                s.setPosition(i * w, j * w);
                app.draw(s);
                s.setTextureRect(IntRect(HP*w, 0, w, w));
                s.setPosition((mapSize-1)*w, 0);
                app.draw(s);
            }
        

        app.display();
    }

    return 0;
}


void unveal(int sgrid[][12], Field* grid[][12], int x, int y) {
    queue <int> q;
    q.push(x);
    q.push(y);

    int a, b;
    while (!q.empty()) {
        a = q.front();
        q.pop();
        b = q.front();
        q.pop();

        sgrid[a][b] = grid[a][b]->getType();

        if (a != mapSize - 2) {
            if (sgrid[a + 1][b] == 10) {
                if (grid[a + 1][b]->getType() == 0) { q.push(a + 1); q.push(b); }
                else { sgrid[a + 1][b] = grid[a + 1][b]->getType(); }
            }
        }
        if (a != 1) {
            if (sgrid[a - 1][b] == 10) {
                if (grid[a - 1][b]->getType() == 0) { q.push(a - 1); q.push(b); }
                else { sgrid[a - 1][b] = grid[a - 1][b]->getType(); }
            }
        }
        if (b != mapSize - 2) {
            if (sgrid[a][b + 1] == 10) {
                if (grid[a][b + 1]->getType() == 0) { q.push(a); q.push(b + 1); }
                else { sgrid[a][b + 1] = grid[a][b + 1]->getType(); }
            }
        }
        if (b != 1) {
            if (sgrid[a][b - 1] == 10) {
                if (grid[a][b - 1]->getType() == 0) { q.push(a); q.push(b - 1); }
                else { sgrid[a][b - 1] = grid[a][b - 1]->getType(); }
            }
        }
    }
}
