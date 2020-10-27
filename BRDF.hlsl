#ifndef BRDF_HLSL_
#define BRDF_HLSL_

#include "Constant.hlsl"










//========== Fresnel Term ==========//

#define _CALC_SCHLICK_APPROXIMATION_(DUMMY)\
	float negCos = 1.0-satuCosine;\
	return f0+(max(f90, f0)-f0)*negCos*negCos*negCos*negCos*negCos

// F0
inline float calcF0FromIOR(float ior)
{
	return pow((ior-1.0)/(ior+1.0), 2.0);
}

// Schlick Approximation for Non-metal
inline float calcSchlickApproximation(float f0, float f90, float satuCosine)
{
	_CALC_SCHLICK_APPROXIMATION_(0);
}
inline float calcSchlickApproximation(float f0, float satuCosine)
{
	return calcSchlickApproximation(f0, 1.0, satuCosine);
}

// Schlick Approximation for Metal
inline float3 calcSchlickApproximation(float3 f0, float3 f90, float satuCosine)
{
	_CALC_SCHLICK_APPROXIMATION_(0);
}
inline float3 calcSchlickApproximation(float3 f0, float satuCosine)
{
	return calcSchlickApproximation(f0, 1.0, satuCosine);
}





//========== Distribution Term ==========//

// GGX Distribution
inline float calcGGXDistribution(float satuHdotN, float alphaSquared)
{
	float x = 1.0-(1.0-alphaSquared)*satuHdotN*satuHdotN;
	return alphaSquared/(PI*x*x);
}





//========== Geometry Term ==========//

// Smith Joint Masking Shadow
inline float calcSmithJointMaskingShadowingLambda(float dotFactor, float alphaSquared)
{
	return sqrt(1.0+alphaSquared*(1.0/(dotFactor*dotFactor)-1.0))*0.5-0.5;
}
inline float calcSmithJointMaskingShadowing(float LdotN, float VdotN, float alphaSquared)
{
	return 1.0/(1.0+calcSmithJointMaskingShadowingLambda(LdotN, alphaSquared)+calcSmithJointMaskingShadowingLambda(VdotN, alphaSquared));
}










//========== Lambert BRDF ==========//

inline float3 calcLambertBRDF(float3 reflectance)
{
	return reflectance;
}
inline float3 calcNormalizedLambertBRDF(float3 reflectance)
{
	return calcLambertBRDF(reflectance)*PI_INV;
}





//========== Half Lambert BRDF ==========//

inline float3 calcHalfLambertBRDF(float3 reflectance, float cosTerm)
{
	float lambert = cosTerm*0.5+0.5;
	return lambert*lambert*reflectance;
}
inline float3 calcNormalizedHalfLambertBRDF(float3 reflectance, float cosTerm)
{
	return calcHalfLambertBRDF(reflectance, cosTerm)*3.0/(2.0*TWO_PI);
}





//========== Disney BRDF ==========//

inline float3 calcDisneyDiffuseBRDF(float3 reflectance, float satuLdotH, float satuLdotN, float satuVdotN, float roughness)
{
	float f90 = 0.5+2.0*satuLdotH*satuLdotH*roughness;
	return reflectance*calcSchlickApproximation(1.0, f90, satuLdotN)*calcSchlickApproximation(1.0, f90, satuVdotN)*PI_INV;
}
inline float3 calcNormalizedDisneyDiffuseBRDF(float3 reflectance, float satuLdotH, float satuLdotN, float satuVdotN, float roughness)
{
	float f90 = lerp(0.0, 0.5, roughness)+2.0*satuLdotH*satuLdotH*roughness;
	return reflectance*calcSchlickApproximation(1.0, f90, satuLdotN)*calcSchlickApproximation(1.0, f90, satuVdotN)*PI_INV*lerp(1.0, 1.0/1.51, roughness);
}





//========== Phong BRDF ==========//

inline float3 calcPhongBRDF(float3 reflectance, float satuRdotL, float n)
{
	return pow(satuRdotL, n)*reflectance;
}
inline float3 calcNormalizedPhongBRDF(float3 reflectance, float satuRdotL, float n)
{
	return calcPhongBRDF(reflectance, satuRdotL, n)*(n+2.0)*TWO_PI_INV;
}





//========== Blinn Phong BRDF ==========//

inline float3 calcBlinnPhongBRDF(float3 reflectance, float satuHdotN, float n)
{
	return pow(satuHdotN, n)*reflectance;
}
inline float3 calcNormalizedBlinnPhongBRDF(float3 reflectance, float satuHdotN, float n)
{
	return calcBlinnPhongBRDF(reflectance, satuHdotN, n)*(n+2.0)*(n+4.0)/(8.0*PI*(pow(2, -n*0.5)+n));
}





//========== Oren Nayer BRDF ==========//

inline float3 calcOrenNayerBRDF(float3 reflectance, float3 normal, float3 lightDirection, float3 viewDirection, float satuVdotN, float satuLdotN, float roughnessSquared)
{
	float sinNV = sqrt(1.0-satuVdotN*satuVdotN);
    float sinNL = sqrt(1.0-satuLdotN*satuLdotN);
	return reflectance*(1.0-0.5*roughnessSquared/(roughnessSquared+0.33)+0.45*roughnessSquared*dot(normalize(viewDirection-satuVdotN*normal), normalize(lightDirection-satuLdotN*normal))*(satuVdotN < satuLdotN ? sinNV : sinNL)*(satuVdotN > satuLdotN ? sinNV/satuVdotN : sinNL/satuLdotN)/(roughnessSquared+0.09))*PI_INV;
}





//========== Cook Torrance BRDF ==========//

inline float3 calcCookTorranceBRDF(float3 reflectance, float D, float G, float F, float absLdotN, float absVdotN)
{
	return reflectance*D*G*F/(PI*absLdotN*absVdotN);
}





//========== Torrance Sparrow BRDF ==========//

inline float3 calcTorranceSparrowBRDF(float3 reflectance, float D, float G, float F, float absLdotN, float absVdotN)
{
	return reflectance*D*G*F/(4.0*absLdotN*absVdotN);
}










#endif