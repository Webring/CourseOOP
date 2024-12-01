#ifndef PLOTTER_H
#define PLOTTER_H

#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>

#define GNUPLOT_CMD_COMMAND "gnuplot"

using namespace std;

class Plotter {
private:
    string title;
    vector<string> plotCommands;

    FILE *newGnuplot();
    int closeGnuplot(FILE *gnuplot);
    void removeFiles();
    string dataFileName(int id);
    string dataToFile(vector<double> &x, vector<double> &y);
    void sendPlotCommands(FILE *gnuplot);

public:
    void clearPlots();
    void setTitle(const string &title);
    void plot(vector<double> &x, vector<double> &y, string name = "");
    void scatter(vector<double> &x, vector<double> &y, string name = "");
    void show();
    void save(string &filename);
    ~Plotter();
};

#endif // PLOTTER_H
