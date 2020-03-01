#include <iostream>
#include<memory>
#include <yaml-cpp/yaml.h>
#include<jaegertracing/Tracer.h>
#include<chrono>

using namespace std;
// using namespace literals::chrono_literals;

void init(const char *FilePath)
{
    auto yaml = YAML::LoadFile(FilePath);
    auto config = jaegertracing::Config::parse(yaml);
    auto tracer=jaegertracing::Tracer::make(
        "example-service-2",
        config,
        jaegertracing::logging::consoleLogger()
    );
    opentracing::Tracer::InitGlobal(
        static_pointer_cast<opentracing::Tracer>(tracer)
    );
}

void ChildSpan(const unique_ptr<opentracing::Span>& parentSpan){
    this_thread::sleep_for(chrono::milliseconds(2));
    auto childSpan = opentracing::Tracer::Global()->StartSpan("Span2",{opentracing::ChildOf(&parentSpan->context())});
}

void FollowsSpan(const unique_ptr<opentracing::Span>& followFromspan){
    this_thread::sleep_for(chrono::milliseconds(3));
    auto followSpan = opentracing::Tracer::Global()->StartSpan("Span3",{opentracing::FollowsFrom(&followFromspan->context())});
}

void ParentSpan(){
    auto span = opentracing::Tracer::Global()->StartSpan("Span1");
    ChildSpan(span);
    FollowsSpan(span);
    this_thread::sleep_for(chrono::milliseconds(4));
}

int main()
{
    init("./config.yaml");
    ParentSpan();
    cout<<"Hello World"<<endl;
    opentracing::Tracer::Global()->Close();
    return 0;
}

