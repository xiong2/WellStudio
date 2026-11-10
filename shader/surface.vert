#version 120

in vec3 myVertex;
in vec3 myNormal;
in float myAttr;
varying float myAttrInter;
varying vec4 internsity;
uniform int lightState[4];
uniform bool baseMap;
void main(void)
{
  if(!baseMap)
 {  
	vec3 norm = normalize(gl_NormalMatrix * (myNormal));
   vec3 intensityAcc=vec3(0.0,0.0,0.0);
   for(int i=0;i<4;i++)
   {
		if(lightState[i]==1)
		{
			 vec3 lightDir=normalize(gl_LightSource[i].position.xyz);
			 vec3 lightHalfVec=normalize(gl_LightSource[i].halfVector.xyz);
			 float diffusefract = max( dot(lightDir,norm) , 0.0);
			 float specularfract=0.0f;
			 if( diffusefract > 0.0)
			 {
			  
			   specularfract = max( dot(lightHalfVec,norm) , 0.0);
			   specularfract = pow(specularfract, 20);
			}
			intensityAcc+=vec3(0.6*gl_LightSource[i].ambient.xyz 
                  + 0.3* gl_LightSource[i].diffuse.xyz * diffusefract 
                  + 0.1* gl_LightSource[i].specular.xyz * specularfract);
				 
		}

   }
   internsity=vec4(intensityAcc,1);
  }
   myAttrInter=myAttr;
   gl_Position  = gl_ModelViewProjectionMatrix * vec4(myVertex,1);
}
