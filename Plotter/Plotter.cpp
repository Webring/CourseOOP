#include "Plotter.h"

FILE *Plotter::newGnuplot() {
    FILE *newInstance = popen(GNUPLOT_CMD_COMMAND " -persistent", "w");
    if (!newInstance) {
        throw runtime_error("gnuplot opening error");
    }
    return newInstance;
}

int Plotter::closeGnuplot(FILE *gnuplot) {
    return pclose(gnuplot);
}

void Plotter::removeFiles() {
    for (int i = 0; i < plotCommands.size(); i++) {
        string filename = dataFileName(i);
        if (remove(filename.c_str())) {
            throw runtime_error(("Can't delete file " + filename).c_str());
        }
    }
}

string Plotter::dataFileName(int id) {
    return "data_" + to_string(id) + ".txt";
}

string Plotter::dataToFile(vector<double> &x, vector<double> &y) {
    if (x.size() != y.size()) {
        throw runtime_error("Arrays have different sizes");
    }

    string newFileName = dataFileName(plotCommands.size());
    ofstream file(newFileName);

    for (int i = 0; i < x.size(); i++) {
        file << x[i] << " " << y[i];
        if (i < x.size() - 1) {
            file << endl;
        }
    }
    file.close();
    return newFileName;
}

void Plotter::sendPlotCommands(FILE *gnuplot) {
    if (!title.empty()) {
        fprintf(gnuplot, "set title '%s'\n", title.c_str());
    }

    fprintf(gnuplot, "plot ");
    for (size_t i = 0; i < plotCommands.size(); ++i) {
        fprintf(gnuplot, "%s", plotCommands[i].c_str());
        if (i != plotCommands.size() - 1) {
            fprintf(gnuplot, ", ");
        }
    }
    fprintf(gnuplot, "\n");
}

void Plotter::clearPlots() {
    removeFiles();
    plotCommands.clear();
}

void Plotter::setTitle(const string &title) {
    this->title = title;
}

void Plotter::plot(vector<double> &x, vector<double> &y, string name) {
    string fileName = dataToFile(x, y);

    string newCommand = "'" + fileName + "' with lines";

    if (!name.empty()) {
        newCommand += " title '" + name + "'";
    }

    plotCommands.push_back(newCommand);
}

void Plotter::scatter(vector<double> &x, vector<double> &y, string name) {
    string fileName = dataToFile(x, y);

    string newCommand = "'" + fileName + "' with points";

    if (!name.empty()) {
        newCommand += " title '" + name + "'";
    }

    plotCommands.push_back(newCommand);
}

void Plotter::show() {
    if (plotCommands.empty()) {
        return;
    }

    FILE *gnuplot = newGnuplot();

    sendPlotCommands(gnuplot);

    closeGnuplot(gnuplot);
}

void Plotter::save(string &filename) {
    if (plotCommands.empty()) {
        return;
    }

    FILE *gnuplot = newGnuplot();

    fprintf(gnuplot, "set terminal png\n");
    fprintf(gnuplot, "set output '%s.png'\n", filename.c_str());

    sendPlotCommands(gnuplot);

    closeGnuplot(gnuplot);
}

Plotter::~Plotter() {
    clearPlots();
}
