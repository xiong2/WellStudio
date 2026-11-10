#version 120

varying float myAttrInter; 
varying vec4 internsity;
uniform bool baseMap;
uniform vec4 colorTable[256];

void main(void)
{
 
   int curindex=int(myAttrInter*255.0f);
   
  
	 if(!baseMap)
	 {
		 gl_FragColor=colorTable[curindex]*internsity;
		
	 }else
	 {
		 gl_FragColor=colorTable[curindex];
	 }
}