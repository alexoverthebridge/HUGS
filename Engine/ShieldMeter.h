#include "Drawable.h"
#include "Ship.h"

class ShieldMeter
{
private:
	class Drawable : public ::Drawable
	{
	public:
		Drawable( const ShieldMeter& parent )
			:
			parent( parent )
		{}
		virtual void Rasterize( D3DGraphics& gfx ) const override
		{
			const Color meterColor = 
				{ unsigned char(255 * (1.0f - parent.ship.GetShieldPercent())),0,0 };
			const int meterWidth = int( ( ( parent.region.right - parent.region.left ) -
				( 2 * parent.borderWidth + 2 * parent.spaceWidth ) ) * parent.ship.GetShieldPercent() );
			gfx.DrawRectangle( parent.region.left,parent.region.right,
				parent.region.top,parent.region.top + (parent.borderWidth - 1),
				parent.borderColor );
			gfx.DrawRectangle( parent.region.left,parent.region.left + (parent.borderWidth - 1),
				parent.region.top + parent.borderWidth,
				parent.region.bottom - parent.borderWidth,parent.borderColor );
			gfx.DrawRectangle( parent.region.right - parent.borderWidth,parent.region.right,
				parent.region.top + parent.borderWidth,parent.region.bottom - parent.borderWidth,
				parent.borderColor );
			gfx.DrawRectangle( parent.region.left,parent.region.right,
				parent.region.bottom - (parent.region.bottom - 1),parent.region.bottom,parent.borderColor );
			gfx.DrawRectangle( parent.region.left + parent.borderWidth + parent.spaceWidth,
				parent.region.left + parent.borderWidth + parent.spaceWidth + meterWidth,
				parent.region.top + parent.borderWidth + parent.spaceWidth,
				parent.region.bottom - ( parent.borderWidth + parent.spaceWidth ),meterColor );
		}
	private:
		const ShieldMeter& parent;
	};
public:
	ShieldMeter( const RectI region,const Ship& ship )
		:
		region( region ),
		ship( ship )
	{}
	Drawable GetDrawable() const
	{
		return Drawable( *this );
	}
private:
	const int borderWidth = 5;
	const int spaceWidth = 3;
	const Color borderColor = WHITE;
	const RectI region;
	const Ship& ship;
};