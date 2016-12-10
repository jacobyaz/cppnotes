#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;
typedef vector<vector<int> > Matrix;
typedef pair<int,int> pixel;
typedef vector<pixel> Pixels;

int lastCluster = 0;

bool isInRange(pixel const & p, int const numRow, int const numCol) {
	auto x = p.first; 
	auto y = p.second;
	return x >=0 && x < numRow && y>=0 && y < numCol;
}

bool isFeasible(pixel const & p, int const numRow, int const numCol, Matrix const & visited) {
	auto x = p.first; 
	auto y = p.second;

	return isInRange(p,numRow,numCol) && visited[x][y]!=2;
}

void addPixelToQ(pixel const & p, queue<pixel> & q, Matrix & visited ) {
	if (!visited[p.first][p.second] == 1) {
		visited[p.first][p.second] = 1;
		q.push(p);
	}
}

Pixels getNeighbors(pixel const & p, int const numRow, int const numCol) {
	auto x = p.first; 
	auto y = p.second;
	Pixels s;

	auto lPixel = make_pair(p.first, p.second - 1);
	if (isInRange(lPixel, numRow, numCol)) s.emplace_back(lPixel);
	auto tPixel = make_pair(p.first-1, p.second);
	if (isInRange(tPixel, numRow, numCol)) s.emplace_back(tPixel);
	auto rPixel = make_pair(p.first, p.second + 1);
	if (isInRange(rPixel, numRow, numCol)) s.emplace_back(rPixel);
	auto bPixel = make_pair(p.first+1, p.second);
	if (isInRange(bPixel, numRow, numCol)) s.emplace_back(bPixel);
	
	return s;
}

void visitPixel(pixel const & p, int const numRow, int const numCol, Matrix const & image, Matrix & c, Matrix & visited ) {
	auto x = p.first; 
	auto y = p.second;

	visited[x][y] = 2;
	if (image[x][y]) {
		int clusterFound = 0;
		for (auto n : getNeighbors(p,numRow,numCol)) {
			if (c[n.first][n.second] > 0) {
				clusterFound = c[n.first][n.second];
				break;
			}
		}
		if (clusterFound > 0) {
			c[x][y] = clusterFound;
		} else {
			c[x][y] = ++lastCluster;
		}
	}
}

void printMatrix(Matrix const & m) {
	auto numRow = m.size();
	auto numCol = m[0].size();
	
	for (int ii=0;ii<numRow;++ii) {
		for (int jj=0;jj<numCol;++jj) {
			cout << m[ii][jj] << ",";
		}
		cout << endl;
	}
}

void findClusters(Matrix const & image) {
	auto numRow = image.size();
	auto numCol = image[0].size();
	
	vector<int> rowZeros(numCol, 0);
	Matrix visited(numRow, rowZeros);
	Matrix cluster(numRow, rowZeros);

	queue<pixel> q;
	q.push(make_pair(0,0));
	while (!q.empty()) {
		auto p = q.front(); q.pop();
		
		visitPixel(p, numRow, numCol, image, cluster, visited);

		auto s = getNeighbors(p, numRow, numCol);
		for (auto n : s) {
			if (isFeasible(n, numRow, numCol, visited)) addPixelToQ(n,q,visited);
		}
	}
	cout << "Image:" << endl;
	printMatrix(image);	
	cout << "Cluster:" << endl;	
	printMatrix(cluster);
}

int main() {
	Matrix image={{0,0,0,0,0},
	              {0,1,1,0,0},
	              {0,1,1,0,0},
	              {0,0,0,1,0},
	              {0,0,0,0,1}};
	findClusters(image);
}

