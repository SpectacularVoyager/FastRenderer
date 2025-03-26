#include "Renderer/Renderer.h"

void Renderer::Add(Renderable* r){
	objects.push_back(r);
}
void Renderer::Loop(){
	RenderToFB();
}
void Renderer::RenderShadow(){

	for(Renderable* r:objects){
		r->Bind();
		ShaderProgram& shader=r->GetShader();
		shader.Use();
		shader.setInt("Texture",2);
		Scene::getScene().setGlobalUniforms(shader);
		shader.setMat4f("model",r->getTransform());
		r->Draw();
	}
}

void Renderer::RenderToFB(){
	fb.Bind();
	Scene::getScene().PrepareFrameBufferRender();
	for(Renderable* r:objects){
		r->Bind();
		ShaderProgram& shader=r->GetShader();
		shader.Use();
		shader.setInt("Texture",2);
		Scene::getScene().setGlobalUniforms(shader);
		shader.setMat4f("model",r->getTransform());
		r->Draw();
	}
	fb.UnBind();
	Scene::getScene().AfterFrameBufferRender();
	fb.GetTexture().Bind(0);
	RenderScreenQuad();
}
void Renderer::RenderImGUI(ImGuiIO& io){

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


		{
			ImGui::Begin("Render Stats");
			ImGui::Text("Time: %.3f ms | %.1f FPS", 1000.0f / io.Framerate, io.Framerate);
            //ImGui::SliderFloat("speed", &speed, 0.0f, 0.5f);
			ImGui::End();
		}

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}
void Renderer::RenderScreenQuad(){
	quad.Bind();
	quad.Draw();
}
