#include "GameObjects/Cat.h"
#include <queue>
#include <iostream>
#include "Level.h"


Cat::Cat(int movementSpeed, sf::Sprite sprite, Level& level) :MovingObject(movementSpeed,sprite),
m_level(level)
{
	sprite.setOrigin(16, 16);
	setSprite(sprite);
}


struct Node {
	int x;
	int y;
	Node(int _x, int _y) {
		x = _x;
		y = _y;
	};
};

void Cat::setDirections(sf::Vector2f mousePos)
{
	// Variables
	std::vector<std::vector<bool>> visited(ROWS, std::vector<bool>(COLS, false));
	std::vector<std::vector<Node>> path(ROWS, std::vector<Node>(COLS, { -1,-1 }));
	std::queue<Node> myQueue;
	
	sf::Vector2f catPos = getPosition();


	// Off set the origin
	Direction dir = getDirection();
	if (dir == RIGHT || dir == DOWN) {
		catPos.x -= 16.f;
		catPos.y -= 16.f;
	}
	if (dir == LEFT || dir == UP) {
		catPos.x += 16.f;
		catPos.y += 16.f;
	}

	Node catNode(catPos.x / TEXTURESIZE, catPos.y / TEXTURESIZE);
	Node startingNode(mousePos.x / TEXTURESIZE, mousePos.y / TEXTURESIZE);
	visited[startingNode.y][startingNode.x] = true;
	path[startingNode.y][startingNode.x] = startingNode;

	myQueue.push(startingNode);

	while (!myQueue.empty()) {
		Node currNode = myQueue.front();
		myQueue.pop();



		if (currNode.x == catNode.x && currNode.y == catNode.y) {
			break;
		}

		//Left
		if (currNode.x - 1 >= 0 && !visited[currNode.y][currNode.x - 1] && !m_level.checkIfObstacle(currNode.y,currNode.x-1)) {
			Node neighbor(currNode.x - 1, currNode.y);
			myQueue.push(neighbor);
			visited[neighbor.y][neighbor.x] = true;
			path[neighbor.y][neighbor.x] = currNode;
		}

		// UP
		if (currNode.y - 1 >= 0 && !visited[currNode.y-1][currNode.x]&& !m_level.checkIfObstacle(currNode.y-1, currNode.x)) {
			Node neighbor(currNode.x, currNode.y-1);
			myQueue.push(neighbor);
			visited[neighbor.y][neighbor.x] = true;
			path[neighbor.y][neighbor.x] = currNode;
		}
		// Right
		if (currNode.x + 1 < COLS && !visited[currNode.y][currNode.x+1] && !m_level.checkIfObstacle(currNode.y, currNode.x + 1)) {
			Node neighbor(currNode.x + 1, currNode.y);
			myQueue.push(neighbor);
			visited[neighbor.y][neighbor.x] = true;
			path[neighbor.y][neighbor.x] = currNode;
		}
		// Down
		if (currNode.y + 1 < ROWS && !visited[currNode.y+1][currNode.x] && !m_level.checkIfObstacle(currNode.y+1, currNode.x)) {
			Node neighbor(currNode.x, currNode.y + 1);
			myQueue.push(neighbor);
			visited[neighbor.y][neighbor.x] = true;
			path[neighbor.y][neighbor.x] = currNode;
		}
	}

	Node nextMove = path[catNode.y][catNode.x];


	if (nextMove.x == -1) {
		setDirection(STANDING);
		return;
	}

	else if (nextMove.x < catNode.x) {
		setDirection(LEFT);
	}
	else if (nextMove.x > catNode.x) {
		setDirection(RIGHT);
	}
	else if (nextMove.y > catNode.y) {
		setDirection(DOWN);
	}
	if (nextMove.y < catNode.y) {
		setDirection(UP);
	}

}

void Cat::handleCollision(GameObject& gameobject)
{
	gameobject.handleCollision(*this);
}
