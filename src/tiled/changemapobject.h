/*
 * changemapobject.h
 * Copyright 2009, Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CHANGEMAPOBJECT_H
#define CHANGEMAPOBJECT_H

#include "tilelayer.h"

#include <QUndoCommand>
#include <QVector>

namespace Tiled {

class MapObject;
class Tile;

namespace Internal {

class MapDocument;
class MapObjectModel;

class ChangeMapObject : public QUndoCommand
{
public:
    /**
     * Creates an undo command that sets the given \a object's \a name and
     * \a type.
     */
    ChangeMapObject(MapDocument *mapDocument,
                    MapObject *object,
                    const QString &name,
                    const QString &type);

    void undo() override { swap(); }
    void redo() override { swap(); }

private:
    void swap();

    MapDocument *mMapDocument;
    MapObject *mMapObject;
    QString mName;
    QString mType;
};

/**
 * Used for changing object visibility.
 */
class SetMapObjectVisible : public QUndoCommand
{
public:
    SetMapObjectVisible(MapDocument *mapDocument,
                        MapObject *mapObject,
                        bool visible);

    void undo() override;
    void redo() override;

private:
    MapObjectModel *mMapObjectModel;
    MapObject *mMapObject;
    bool mOldVisible;
    bool mNewVisible;
};


struct MapObjectCell
{
    MapObject *object;
    Cell cell;
};

class ChangeMapObjectCells : public QUndoCommand
{
public:
    /**
     * Creates an undo command that applies the given map object changes.
     */
    ChangeMapObjectCells(MapDocument *mapDocument,
                         const QVector<MapObjectCell> &changes,
                         QUndoCommand *parent = nullptr);

    void undo() override { swap(); }
    void redo() override { swap(); }

private:
    void swap();

    MapObjectModel *mMapObjectModel;
    QVector<MapObjectCell> mChanges;
};

} // namespace Internal
} // namespace Tiled

#endif // CHANGEMAPOBJECT_H
