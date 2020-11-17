#ifndef SHADER_CONSTANT_H
#define SHADER_CONSTANT_H










#ifdef HLSL_
	#define Packoffset(index, dim) :packoffset(c##index##.##dim)
	#define RegisterB(index) :register(b##index)
	#define CBuffer cbuffer
	#define CppLine(code)
#else
	#define Packoffset(index, dim)
	#define RegisterB(index) 
	#define CBuffer struct
	#define CppLine(code) code
#endif

#define MATERIAL_CONSTANT_BUFFER_NAME  Material
#define TRANSFORM_CONSTANT_BUFFER_NAME Transform
#define LIGHT_CONSTANT_BUFFER_NAME     Light










#define DEFINE_SIMPLE_PBR_MATERIAL_CONSTANT_(NAME, index)\
	CBuffer NAME RegisterB(index)\
	{\
		float3_12byte color;\
		float1_4byte roughness;\
		float1_4byte metalness;\
		float1_12byte ior;\
	};





#define DEFINE_SIMPLE_DIRECTIONAL_LIGHT_CONSTANT_(DUMMY)\
    struct SimpleDirectionalLight\
    {\
        float3_16byte color;\
        float3_16byte direction;\
    };
#define DEFINE_SIMPLE_POINT_LIGHT_CONSTANT_(DUMMY)\
    struct SimplePointLight\
    {\
        float3_16byte color;\
        float3_16byte position;\
        float3_16byte Kclq;\
	};
#define DEFINE_SIMPLE_LIGHT_CONSTANT_(NAME, index)\
	CBuffer NAME RegisterB(index)\
	{\
		SimpleDirectionalLight directionalLight;\
		SimplePointLight       pointLights[1];\
\
		float3_16byte          cameraPosition;\
	};





#define DEFINE_DEPTH_LINEARIZER_CONSTANT_(index)\
	CBuffer DepthLinearizer RegisterB(index)\
	{\
		float1_4byte nearZ;\
		float1_12byte farZ;\
	};





#define DEFINE_TRANSFORM_WVP_SHADER_CONSTANT_(NAME, index)\
	CBuffer NAME RegisterB(index)\
	{\
		float4x4 wvp;\
	};
#define DEFINE_TRANSFORM_WVP_LWVP_SHADER_CONSTANT_(NAME, index)\
	CBuffer NAME RegisterB(index)\
	{\
		float4x4 wvp;\
		float4x4 lwvp;\
	};

#define DEFINE_TRANSFORM_WVP_N_SHADER_CONSTANT_(NAME, index)\
	CBuffer NAME RegisterB(index)\
	{\
		float4x4 wvp;\
		float4x4 n;\
	};
#define DEFINE_TRANSFORM_W_VP_N_SHADER_CONSTANT_(NAME, index)\
	CBuffer NAME RegisterB(index)\
	{\
		float4x4 w;\
		float4x4 vp;\
		float4x4 n;\
	};
#define DEFINE_TRANSFORM_W_VP_N_LWVP_SHADER_CONSTANT_(NAME, index)\
	CBuffer NAME RegisterB(index)\
	{\
		float4x4 w;\
		float4x4 vp;\
		float4x4 n;\
		float4x4 lwvp;\
	};

#define DEFINE_TRANSFORM_W_WVP_N_SHADER_CONSTANT_(NAME, index)\
	CBuffer NAME RegisterB(index)\
	{\
		float4x4 w;\
        float4x4 wvp;\
		float4x4 n;\
	};
#define DEFINE_TRANSFORM_W_WVP_N_LWVP_SHADER_CONSTANT_(NAME, index)\
	CBuffer NAME RegisterB(index)\
	{\
		float4x4 w;\
        float4x4 wvp;\
		float4x4 n;\
		float4x4 lwvp;\
	};










#define Define_SimpleLight_HLSL(index)\
	DEFINE_SIMPLE_DIRECTIONAL_LIGHT_CONSTANT_(DUMMY)\
	DEFINE_SIMPLE_POINT_LIGHT_CONSTANT_(DUMMY)\
	DEFINE_SIMPLE_LIGHT_CONSTANT_(LIGHT_CONSTANT_BUFFER_NAME, index)

#define Define_SimplePBRMaterial_HLSL(index)\
	DEFINE_SIMPLE_PBR_MATERIAL_CONSTANT_(MATERIAL_CONSTANT_BUFFER_NAME, index)

#define Define_DepthLinearizer_HLSL(index)\
	DEFINE_DEPTH_LINEARIZER_CONSTANT_(index)





#define Define_TransformWVP_HLSL(index)\
	DEFINE_TRANSFORM_WVP_SHADER_CONSTANT_(TRANSFORM_CONSTANT_BUFFER_NAME, index)
#define Define_TransformWVP_N_HLSL(index)\
	DEFINE_TRANSFORM_WVP_N_SHADER_CONSTANT_(TRANSFORM_CONSTANT_BUFFER_NAME, index)
#define Define_TransformW_VP_N_HLSL(index)\
	DEFINE_TRANSFORM_W_VP_N_SHADER_CONSTANT_(TRANSFORM_CONSTANT_BUFFER_NAME, index)
#define Define_TransformW_WVP_N_HLSL(index)\
	DEFINE_TRANSFORM_W_WVP_N_SHADER_CONSTANT_(TRANSFORM_CONSTANT_BUFFER_NAME, index)
#define Define_TransformWVP_LWVP_HLSL(index)\
	DEFINE_TRANSFORM_WVP_LWVP_SHADER_CONSTANT_(TRANSFORM_CONSTANT_BUFFER_NAME, index)
#define Define_TransformW_VP_N_LWVP_HLSL(index)\
	DEFINE_TRANSFORM_W_VP_N_LWVP_SHADER_CONSTANT_(TRANSFORM_CONSTANT_BUFFER_NAME, index)
#define Define_TransformW_WVP_N_LWVP_HLSL(index)\
	DEFINE_TRANSFORM_W_WVP_N_LWVP_SHADER_CONSTANT_(TRANSFORM_CONSTANT_BUFFER_NAME, index)





#define DEFINE_SHADER_CONSTANT_C(DUMMY)\
	DEFINE_TRANSFORM_WVP_SHADER_CONSTANT_(TransformWVP)\
	DEFINE_TRANSFORM_WVP_N_SHADER_CONSTANT_(TransformWVP_N)\
	DEFINE_TRANSFORM_W_VP_N_SHADER_CONSTANT_(TransformW_VP_N)\
	DEFINE_TRANSFORM_W_WVP_N_SHADER_CONSTANT_(TransformW_WVP_N)\
	DEFINE_TRANSFORM_WVP_LWVP_SHADER_CONSTANT_(TransformWVP_LWVP)\
	DEFINE_TRANSFORM_W_VP_N_LWVP_SHADER_CONSTANT_(TransformW_VP_N_LWVP)\
	DEFINE_TRANSFORM_W_WVP_N_LWVP_SHADER_CONSTANT_(TransformW_WVP_N_LWVP)\
	DEFINE_SIMPLE_PBR_MATERIAL_CONSTANT_(SimplePBRMaterial)\
	DEFINE_SIMPLE_DIRECTIONAL_LIGHT_CONSTANT_()\
    DEFINE_SIMPLE_POINT_LIGHT_CONSTANT_()\
	DEFINE_SIMPLE_LIGHT_CONSTANT_(SimpleLight)\
	DEFINE_DEPTH_LINEARIZER_CONSTANT_()










#endif