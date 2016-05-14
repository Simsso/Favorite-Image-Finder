#ifndef QFILEINFOPAIR_H
#define QFILEINFOPAIR_H

#include <QFileInfo>

struct QFileInfoPair {
    const QFileInfo *a, *b;
    bool equal() const {
        return a == b;
    }
};

#endif // QFILEINFOPAIR_H
