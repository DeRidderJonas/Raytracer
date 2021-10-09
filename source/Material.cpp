#include "Material.h"

Material::Material(const Elite::RGBColor& color)
	: m_Color{color}
{
}

const Elite::RGBColor& Material::getColor() const
{
	return m_Color;
}

Elite::RGBColor Material::GetColorForMetal(const BaseMaterial& metal)
{
	switch (metal)
	{
	case Material::BaseMaterial::Titanium:
		return Elite::RGBColor(0.542f, 0.497f, 0.449f);
		break;
	case Material::BaseMaterial::Chromium:
		return Elite::RGBColor(0.549f, 0.556f, 0.554f);
		break;
	case Material::BaseMaterial::Iron:
		return Elite::RGBColor(0.562f, 0.565f, 0.578f);
		break;
	case Material::BaseMaterial::Nickel:
		return Elite::RGBColor(0.660f, 0.609f, 0.526f);
		break;
	case Material::BaseMaterial::Platinum:
		return Elite::RGBColor(0.673f, 0.637f, 0.585f);
		break;
	case Material::BaseMaterial::Copper:
		return Elite::RGBColor(0.955f, 0.638f, 0.538f);
		break;
	case Material::BaseMaterial::Palladium:
		return Elite::RGBColor(0.733f, 0.697f, 0.652f);
		break;
	case Material::BaseMaterial::Mercury:
		return Elite::RGBColor(0.781f, 0.780f, 0.778f);
		break;
	case Material::BaseMaterial::Brass:
		return Elite::RGBColor(0.910f, 0.778f, 0.423f);
		break;
	case Material::BaseMaterial::Zinc:
		return Elite::RGBColor(0.664f, 0.824f, 0.850f);
		break;
	case Material::BaseMaterial::Gold:
		return Elite::RGBColor(1.f, 0.782f, 0.344f);
		break;
	case Material::BaseMaterial::Aluminum:
		return Elite::RGBColor(0.913f, 0.922f, 0.924f);
		break;
	case Material::BaseMaterial::Silver:
		return Elite::RGBColor(0.972f, 0.960f, 0.915f);
		break;
	case Material::BaseMaterial::Dielectric:
	default:
		return Elite::RGBColor(0.4f, 0.4f, 0.4f);
		break;
	}
}
