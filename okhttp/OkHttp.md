# OkHttp

怎么做到线程安全的？

```java
public static void main(String... args) {

        OkHttpClient.Builder builder = new OkHttpClient.Builder();
        OkHttpClient client = builder.build();

        int num = 8;

        CountDownLatch startGate = new CountDownLatch(1);
        CountDownLatch endGate = new CountDownLatch(num);
        for (int i = 1; i <= num; i++) {
            int p = i;
            Thread t = new Thread() {
                @Override
                public void run() {
                    // 使线程在此等待，当开始门打开时，一起涌入门中
                    try {
                        for (int j = 0; j < 9; j++) {
//                            post(j, client);
                            int x = (p + j) % 9 + 1;
                            Request request = request(x, client);
                            startGate.await();
                            Call call = client.newCall(request);
                            sleep(10);
                            Response response = call.execute();
                            String res = response.body().string();
                            System.out.println(j + ": req: " + x + " res: " + res + ", equals: " + Objects.equals(String.valueOf(x), res));
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    } finally {
                        endGate.countDown();
                    }
                }
            };
            t.start();
        }
        // 因开启门只需一个开关，所以立马就开启开始门
        startGate.countDown();
        // 等等结束门开启
        try {
            endGate.await();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static Request request(Integer i, OkHttpClient client) {
        Request.Builder requestBuilder = new Request.Builder().url(getHttpsUrl(i));
        requestBuilder.post(RequestBody.create(MediaType.parse("application/json;charset=utf-8"), i.toString()));
        Request request = requestBuilder.build();
        return request;
    }

    private static Call call(Integer i, OkHttpClient client) {
        Request.Builder requestBuilder = new Request.Builder().url(getHttpsUrl(i));
        requestBuilder.post(RequestBody.create(MediaType.parse("application/json;charset=utf-8"), i.toString()));
        Request request = requestBuilder.build();
        try {
            Call call = client.newCall(request);
            return call;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    private static void post(Integer i, OkHttpClient client) {
        Request.Builder requestBuilder = new Request.Builder().url(getHttpsUrl(i));
        requestBuilder.post(RequestBody.create(MediaType.parse("application/json;charset=utf-8"), i.toString()));
        Request request = requestBuilder.build();
        try {
            Call call = client.newCall(request);
            Response response = call.execute();
            String res = response.body().string();
            System.out.println(i + ".res: " + res);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String getHttpsUrl(Integer i) {
        return "http://localhost:8080/" + i;
    }
```

