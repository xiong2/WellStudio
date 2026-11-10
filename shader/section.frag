uniform sampler2D sectionTex;
uniform vec4 colorTable[256];
uniform float coordXS;
uniform float coordXE;
uniform float coordYS;
uniform float coordYE;
uniform bool ifChairMode;
varying vec2 texCoord;
void main(void)
{
    float attValue=texture2D(sectionTex, texCoord).x;
	attValue = clamp(attValue, 0.0, 1.0);
    int curindex=int(attValue*255.0);
	
    bool bX=  false;
    if((texCoord.x<coordXE)&&(texCoord.x>coordXS))
              bX=true;
      
    bool bY=  false;
    if((texCoord.y<coordYE)&&(texCoord.y>coordYS))
            bY=true;
    if(ifChairMode&&bX&&bY)  
    { 
      gl_FragColor=vec4(1,1,1.0,0.0);   
    }
    else
    {
    	gl_FragColor= colorTable[curindex];
    }
}