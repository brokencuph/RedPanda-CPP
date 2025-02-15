/*
 * Copyright (C) 2020-2022 Roy Qu (royqh1979@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef MISCPROCS_H
#define MISCPROCS_H
#include <QPoint>
#include <vector>
#include <memory>
#include <QString>
#include <QSet>
#include "highlighter/base.h"
#include <QPaintDevice>
#include <QTextStream>
#include <QVector>
#include <initializer_list>
//#include <QRect>
//#include <QColor>

class QPainter;
class QRect;
class QColor;

using IntArray = QVector<int>;
using PIntArray = std::shared_ptr<IntArray>;

int minMax(int x, int mi, int ma);
int mulDiv(int a, int b, int c);
void swapInt(int& l, int &r);
BufferCoord maxBufferCoord(const BufferCoord& P1, const BufferCoord& P2);
BufferCoord minBufferCoord(const BufferCoord& P1, const BufferCoord& P2);
QPoint maxPoint(const QPoint& P1, const QPoint& P2);
QPoint minPoint(const QPoint& P1, const QPoint& P2);

PIntArray getIntArray(size_t Count, int InitialValue);

void internalFillRect(QPainter* painter, const QRect& rcPaint, const QColor& color);

// Converting tabs to spaces: To use the function several times it's better
// to use a function pointer that is set to the fastest conversion function.
using ConvertTabsProc = std::function<QString(const QString&, int)>;

ConvertTabsProc GetBestConvertTabsProc(int TabWidth);

// This is the slowest conversion function which can handle TabWidth <> 2^n.
QString ConvertTabs(const QString& Line, int TabWidth);

using ConvertTabsProcEx = std::function<QString(const QString&, int, bool& )>;

ConvertTabsProcEx GetBestConvertTabsProcEx(int TabWidth);
// This is the slowest conversion function which can handle TabWidth <> 2^n.
QString ConvertTabsEx(const QString& Line, int TabWidth, bool& HasTabs);

bool GetHasTabs(const QString& line, int& CharsBefore);

int GetExpandedLength(const QString& aStr, int aTabWidth);

int CharIndex2CaretPos(int Index, int TabWidth,
  const QString& Line);

int CaretPos2CharIndex(int Position, int TabWidth, const QString& Line,
  bool& InsideTabChar);

// search for the first char of set AChars in Line, starting at index Start
int StrScanForCharInSet(const QString& Line, int Start, const QSet<QChar>&  AChars);
// the same, but searching backwards
int StrRScanForCharInSet(const QString& Line, int Start, const QSet<QChar>&  AChars);

int GetEOL(const QString& Line, int start);
int CountLines(const QString& Line, int start);

// Remove all '/' characters from string by changing them into '\.'.
// Change all '\' characters into '\\' to allow for unique decoding.
QString EncodeString(const QString & s);

// Decodes string, encoded with EncodeString.
QString DecodeString(const QString& s);

using  HighlighterAttriProc = std::function<bool(PSynHighlighter Highlighter,
    PSynHighlighterAttribute Attri, const QString& UniqueAttriName,
    QList<void *> Params)>;

// Enums all child highlighters and their attributes of a TSynMultiSyn through a
// callback function.
// This function also handles nested TSynMultiSyns including their MarkerAttri.
bool EnumHighlighterAttris(PSynHighlighter Highlighter,
                           bool SkipDuplicates, HighlighterAttriProc highlighterAttriProc,
                           std::initializer_list<void *> Params);


// Calculates Frame Check Sequence (FCS) 16-bit Checksum (as defined in RFC 1171)
uint16_t CalcFCS(unsigned char* ABuf, int ABufSize);

void SynDrawGradient(QPaintDevice* ACanvas, const QColor& AStartColor, const QColor& AEndColor,
  int ASteps, const QRect& ARect, bool AHorizontal);

SynFontStyles getFontStyles(const QFont& font);

/**
 * Find the first occurency of word char in s, starting from startPos
 * Note: the index of first char in s in 1
 * @return index of the char founded , 0 if not found
 */
int StrScanForWordChar(const QString& s, int startPos);

/**
 * Find the first occurency of non word char in s, starting from startPos
 * Note: the index of first char in s in 1
 * @return index of the char founded , 0 if not found
 */
int StrScanForNonWordChar(const QString& s, int startPos);

/**
 * Find the first occurency of word char in s right to left, starting from startPos
 * Note: the index of first char in s in 1
 * @return index of the char founded , 0 if not found
 */
int StrRScanForWordChar(const QString& s, int startPos);

/**
 * Find the first occurency of non word char in s  right to left, starting from startPos
 * Note: the index of first char in s in 1
 * @return index of the char founded , 0 if not found
 */
int StrRScanForNonWordChar(const QString& s, int startPos);

void ensureNotAfter(BufferCoord& cord1, BufferCoord& cord2);

bool isWordChar(const QChar& ch);

#endif // MISCPROCS_H
