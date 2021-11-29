#version 400 core
in vec3 Normals;
in vec3 FragPos;
uniform vec3 CamPosition;
out vec4 FragColor;
uniform sampler2D textureUnitID;
in vec2 TexCoord;
void main () {
   vec3 lightPos = vec3(0.0f, 20.0f, 20.0f);
   vec3 lightVector = lightPos - FragPos;
   float dot_product = max(dot(normalize(lightVector), normalize(Normals)), 0.0);
   vec4 diffuse = dot_product * vec4(0.385f, 0.647f, 0.812f, 1.0f);
   vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
   float specularStrength = 0.75;
   vec3 viewDir = normalize(CamPosition - FragPos);
   vec3 reflectDir = reflect(-lightVector, Normals);
   float spec = pow(max(dot(normalize(viewDir), normalize(reflectDir)), 0.0), 16);
   vec3 specular = specularStrength * spec * vec3(1.0f, 1.0f, 1.0f);
   FragColor = ambient+diffuse + vec4(specular, 1.0f);
   FragColor = texture(textureUnitID, TexCoord);
}