#include <Shroom.h>
#include <Shroom/Core/EntryPoint.h>

class SandboxApp : public Shroom::Application {
public:
    SandboxApp(const Shroom::ApplicationSpecification& spec) : Application(spec) {}
    virtual ~SandboxApp() = default;
};

Shroom::Application* Shroom::CreateApplication() {
    Shroom::ApplicationSpecification spec{};
    spec.Title = "Shroom Sandbox";
    return new SandboxApp(spec);
}
