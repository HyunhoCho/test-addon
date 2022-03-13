// napi.h 호출, 기본적으로 node-addon-api를 설치하면 그 안에 포함되어 있다.
// 만약 빨간줄이 뜨는 경우, 아래 기술된 내용으로 해결해보자.
#include <napi.h>

// Javascript의 String 객체를 반환하는 함수, 즉 우리가 export 시켜주고 싶은 함수를 만든다.
// 파라미터는 info[n] 형태로 얻어올 수 있다. (param이 2개라면 info[0], info[1] 이런 식으로)
Napi::String HelloWorld(const Napi::CallbackInfo& info) {

  // info에는 현재 scope 정보(env)도 들어있다.
  // js 객체를 생성하려면 반드시 env를 받아와야 함.
  Napi::Env env = info.Env();
  
  // scope info(env)와 std::string 객체를 사용해 문자열 리턴
  return Napi::String::New(env, "Hello World !");
}

// Add-on Initializer.
// js object(exports)에 export 시킬 객체들(함수, 변수 등..)을 넣고 리턴시키면 된다.
Napi::Object init(Napi::Env env, Napi::Object exports) {

  exports.Set(Napi::String::New(env, "HelloWorld"), Napi::Function::New(env, HelloWorld));
  // 더 추가할꺼라면 위와 같은 형식으로 세팅..
  
  return exports;
}

// Add-on이 실제 호출될 때의 alias와 initializer를 인자로 받아 설정함.
NODE_API_MODULE(hello_world, init);