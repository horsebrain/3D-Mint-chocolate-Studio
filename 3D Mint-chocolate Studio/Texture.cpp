
/*
	2017.04.26
	Created by AcrylicShrimp.
*/

#include "Texture.h"

namespace D3MCS::Render
{
	Texture::Texture()
	{
		glGenTextures(1u, &this->nTextureID);
	}

	Texture::Texture(Texture &&sSrc) :
		nTextureID{sSrc.nTextureID}
	{
		sSrc.nTextureID = Texture::ZeroID;
	}

	Texture::~Texture()
	{
		if (this->nTextureID)
			glDeleteTextures(1u, &this->nTextureID);
	}

	Texture &Texture::operator=(Texture &&sSrc)
	{
		if (&sSrc == this)
			return *this;

		this->~Texture();

		this->nTextureID = sSrc.nTextureID;
		sSrc.nTextureID = Texture::ZeroID;

		return *this;
	}

	void Texture::setMinFilteringMode(TexelFilter eTexelFilter, MipmapFilter eMipmapFilter) const
	{
		switch (eMipmapFilter)
		{
		case MipmapFilter::None:
			glTextureParameteri(this->nTextureID, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(eTexelFilter));
			return;
		case MipmapFilter::Linear:
			glTextureParameteri(this->nTextureID, GL_TEXTURE_MIN_FILTER, eTexelFilter == TexelFilter::Linear ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR);
			return;
		case MipmapFilter::Nearest:
			glTextureParameteri(this->nTextureID, GL_TEXTURE_MIN_FILTER, eTexelFilter == TexelFilter::Linear ? GL_LINEAR_MIPMAP_NEAREST : GL_NEAREST_MIPMAP_NEAREST);
			return;
		default:
			return;
		}
	}
}