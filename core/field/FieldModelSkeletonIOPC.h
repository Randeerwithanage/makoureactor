/****************************************************************************
 ** Makou Reactor Final Fantasy VII Field Script Editor
 ** Copyright (C) 2009-2015 Arzel J�r�me <myst6re@gmail.com>
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#ifndef FIELDMODELSKELETONIOPC_H
#define FIELDMODELSKELETONIOPC_H

#include "FieldModelSkeletonIO.h"

class FieldModelSkeletonIOPC : public FieldModelSkeletonIO
{
public:
	explicit FieldModelSkeletonIOPC(QIODevice *io);
	virtual ~FieldModelSkeletonIOPC() {}

	bool read(FieldModelSkeleton &skeleton) const {
		QMultiMap<int, QStringList> rsdFiles;
		return read(skeleton, rsdFiles);
	}
	bool read(FieldModelSkeleton &skeleton, QMultiMap<int, QStringList> &rsdFiles) const;
	bool write(const FieldModelSkeleton &skeleton) const;
};

#endif // FIELDMODELSKELETONIOPC_H