/*
 * This file is part of the KDE project
 *
 * Copyright (c) Michael Thaler <michael.thaler@physik.tu-muenchen.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef _KIS_CUBISM_FILTER_H_
#define _KIS_CUBISM_FILTER_H_

#include "kis_filter.h"
#include "kis_view.h"
#include <kdebug.h>

class KisPolygon;

class KisCubismFilterConfiguration : public KisFilterConfiguration
{
	public:
                KisCubismFilterConfiguration(Q_UINT32 tileSize, Q_UINT32 tileSaturation) : m_tileSize(tileSize), m_tileSaturation(tileSaturation) {};
	public:
                inline Q_UINT32 tileSize() { return m_tileSize; };
                inline Q_UINT32 tileSaturation() {return m_tileSaturation; };
        private:
                Q_UINT32 m_tileSize;
                Q_UINT32 m_tileSaturation;
};

class KisCubismFilter : public KisFilter
{
public:
	KisCubismFilter(KisView * view);
public:
	virtual void process(KisPaintDeviceSP,KisPaintDeviceSP, KisFilterConfiguration* , const QRect&);
	static inline KisID id() { return KisID("cubism", i18n("cubism")); };
	virtual bool supportsPainting() { return true; }
public:
	virtual QWidget* createConfigurationWidget(QWidget* parent);
	virtual KisFilterConfiguration* configuration(QWidget*);
private:
	void randomize_indices (Q_INT32 count, Q_INT32* indices);
        Q_INT32 randomIntRange(Q_INT32 lowestNumber, Q_INT32 highestNumber);
        double   calcAlphaBlend(double *vec, double oneOverDist, double x, double y);
        void convertSegment (Q_INT32 x1, Q_INT32 y1, Q_INT32 x2, Q_INT32  y2, Q_INT32 offset, Q_INT32* min, Q_INT32* max);
        void fillPolyColor(KisPaintDeviceSP src, KisPaintDeviceSP dst, KisPolygon* poly, Q_UINT8* col, Q_UINT8* dest);

};

#endif
