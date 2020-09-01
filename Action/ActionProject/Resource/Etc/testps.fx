// ピクセルシェーダーの入力
struct PS_INPUT
{
	float4 pos    : SV_POSITION ;// 座標(-1~1)
	float4 dif     : COLOR0 ;// カラー値
	float2 uv  : TEXCOORD0 ;	// UV値
};

// ピクセルシェーダーの出力
struct PS_OUTPUT
{
	float4 color      : SV_TARGET0 ;
} ;

// C++ 側で設定する定数の定義

// 描画するテクスチャ
SamplerState smp       : register( s0 ) ;
Texture2D    tex       : register( t0 ) ;
Texture2D    norm       : register( t1 ) ;


// main関数
PS_OUTPUT main( PS_INPUT PSInput )
{
	//PS_OUTPUT PSOutput ;
	PS_OUTPUT pso;
	float2 dist = norm.Sample(smp, PSInput.uv) * 2.0f - 1.0f;
	dist /= float2(40.0f, 30.0f);
	//pso.color = PSInput.dif * PSInput.dif * float4(0.1, 0.2, 1, 1) * tex.Sample(smp, PSInput.uv + dist);
	//pso.color = PSInput.dif * PSInput.dif * float4(0.6, 0.3, 0.4, 1) * tex.Sample(smp, PSInput.uv + dist);
	pso.color = PSInput.dif * PSInput.dif * 0.5f + float4(0.1, 0.2, 1, 1) +tex.Sample(smp, PSInput.uv + dist);
	float2 fmd = fmod(PSInput.uv, 0.1);
	//if(((fmd.x<=0.05) + (fmd.y<=0.05))%2==0)
	//{
	//	//pso.color = float4(0.1, 0.2, 1, 1) + tex.Sample(smp, PSInput.uv);
	//}
	//else
	//{
	//	//pso.color = tex.Sample(smp, PSInput.uv + float2(0.01, 0.0f));
	//}
	
	return pso;
	
//	
//	if(((fmd.x<=0.05) + (fmd.y<=0.05))%2==0 ){
//		PSOutput.Output=float4(1,1,0,1);
//	}else{
//		PSOutput.Output=tex.Sample( smp, PSInput.TexCoords0 ) ;
//	}
	//float4 nuv=norm.Sample(smp,PSInput.uv);
	//PSOutput.Output=PSInput.dif*PSInput.dif+tex.Sample( smp, fmod(PSInput.uv+(nuv.xy*2-float2(1,1))/32.0f,float2(1.0,1.0))  );
	//// 関数の戻り値がラスタライザに渡される
	//return PSOutput ;
}
