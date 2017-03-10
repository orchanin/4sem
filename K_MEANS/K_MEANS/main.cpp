
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"
#include <iostream>
#include <exception>

const int K = 150;
const int iterationCount = 2;

using Centroids = std::vector<sf::Color>;
using ClosestCentroidIndices = std::vector<int>;

Centroids initializeCentroids(sf::Image, int K);
ClosestCentroidIndices findClosestCentroids(sf::Image im, Centroids centrds);
Centroids computeMeans(sf::Image im, ClosestCentroidIndices ind, int k);
void changeColors(sf::Image& im, ClosestCentroidIndices ids, Centroids c);


struct ColorBuf {
    int r, g, b;
    int count = 0;
    ColorBuf& operator += (const sf::Color c)
    {
        count++;
        r += c.r;
        b += c.b;
        g += c.g;
        return *this;
    }
};

int main(int, char const**)
{
    sf::Image im;
    
    
    
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "bird.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    
    im = texture.copyToImage();
    
    
    ClosestCentroidIndices ids;
    Centroids centroids = initializeCentroids(im, K);
    for (int i = 0; i < iterationCount; i++) {
        ids = findClosestCentroids(im, centroids);
        centroids = computeMeans(im, ids, K);
    }
    
    changeColors(im, ids, centroids);
    
    texture.update(im);
    sprite.setTexture(texture);
    
    
    
    
    sf::RenderWindow window(sf::VideoMode(im.getSize().x, im.getSize().y), "SFML window");
    window.clear(sf::Color::White);
    
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        // Clear screen
        window.clear();
        
        // Draw the sprite
        window.draw(sprite);
        
        
        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}

Centroids initializeCentroids(sf::Image im, int K) {
    
    Centroids c;
    
    for (int i = 0; i < K; i++) {
        
        sf::Vector2u pix;
        pix.x = rand() % im.getSize().x;
        pix.y = rand() % im.getSize().y;
        
        sf::Color curCollor = im.getPixel(pix.x, pix.y);
        c.push_back(curCollor);
    }
    return c;
}

ClosestCentroidIndices findClosestCentroids(sf::Image im, Centroids centrds){
    
    ClosestCentroidIndices cirIds;
    cirIds.resize(im.getSize().x * im.getSize().y);
    
    
    std::cout<< centrds.size()<< "\n";
    std::vector<int> longs;
    longs.resize(K);
    
    for (int i = 0; i < im.getSize().x ; i++) {
        for (int j = 0; j < im.getSize().y; j++) {
            for (int k = 0 ; k < K; k++)
            {
                longs[k] =   (im.getPixel(i, j).r - centrds[k].r) * (im.getPixel(i, j).r - centrds[k].r)
                +(im.getPixel(i, j).g - centrds[k].g) * (im.getPixel(i, j).g - centrds[k].g)
                +(im.getPixel(i, j).b - centrds[k].b) * (im.getPixel(i, j).b - centrds[k].b);
            }
            
            int min = longs[0];
            int index = 0;
            
            for (int k = 0 ; k < K; k++) {
                if (min > longs[k]) {
                    min = longs[k];
                    index = k;
                }
            }
            
            cirIds[j * im.getSize().x + i] = index;
            
        }
    }
    return cirIds;
}

Centroids computeMeans(sf::Image im, ClosestCentroidIndices ind, int k)
{
    Centroids c;
    c.resize(K);
    std::vector<ColorBuf> buf;
    buf.resize(K);
    for (int i = 0; i < ind.size(); i++)
    {
        buf[ind[i]] += im.getPixel(i % im.getSize().x, i / im.getSize().x);
    }
    
    
    for (int i = 0; i < K; i++)
    {
        buf[i].r /= buf[i].count+1;
        buf[i].g /= buf[i].count+1;
        buf[i].b /= buf[i].count+1;
    }
    
    
    
    for (int i = 0; i < K; i++)
    {
        c[i] = sf::Color(buf[i].r, buf[i].g, buf[i].b);
    }
    
    return c;
}

void changeColors(sf::Image& im, ClosestCentroidIndices ids, Centroids c)
{
    for (int i = 0; i < ids.size(); i++)
    {
        im.setPixel(i % im.getSize().x, i / im.getSize().x, c[ids[i]]);
    }
}
