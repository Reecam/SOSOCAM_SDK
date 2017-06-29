//
//  串口读写操作.h
//  SoDemon
//
//  Created by sandy on 16/5/16.
//  Copyright © 2016年 feng. All rights reserved.
//

#pragma mark 1.读串口数据
1.读串口数据

1)Cgi命令
http://192.168.0.66:80/read_comm.cgi?user==%@&pwd=%@json=1

2)参数：
192.168.0.66:摄像机IP    [cam ip];
80:摄像机端口号         [cam port];
user:摄像机登录名       [cam user];
Pwd:摄像机登录密码     [cam pwd];

返回：返回一个JSON数据，JSON是一个字典，参数详细意义如下：
error:错误值：
error = 0; 没有错误，成功
error = -3; 网络错误
error = -6; 错误参数
error =  -8; 错误ID
error =  -14;用户名货密码错误

data：读取到的数据，是一个10进制的数组

3)注意：url中如果有特殊字符或中文需要转码

4)示例：

AFHTTPSessionManager *session = [AFHTTPSessionManager manager];
session.responseSerializer.acceptableContentTypes = [NSSet setWithObjects: @"text/plain", nil];

[session GET:@"http://192.168.0.66:80/read_comm.cgi?user=admin&pwd=&json=1" parameters:nil success:^(NSURLSessionDataTask *task, id responseObject) {
    
    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:responseObject  options:NSJSONReadingAllowFragments error:nil];
    NSLog(@"success!result = %@",dic);
    
} failure:^(NSURLSessionDataTask *task, NSError *error) {
    
    NSLog(@"fail!error = %@",error);
}];

#pragma mark 2.写串口数据
2.写串口数据

1)Cgi命令
http://192.168.0.66:80/write_comm.cgi?user=%@&pwd=%@json=1&length=%@data=%@

2）参数：
192.168.0.66:摄像机IP    [cam ip];
80:摄像机端口号         [cam port];
user:摄像机登录名       [cam user];
Pwd:摄像机登录密码     [cam pwd];
length:数据长度         data.length
data:串口数据           例如：data=%01%82

返回：返回一个JSON数据，JSON是一个字典，参数详细意义如下：
error:错误值：
error = 0; 没有错误，成功
error = -3; 网络错误
error = -6; 错误参数
error =  -8; 错误ID
error =  -14;用户名货密码错误

result：写串口结果：
result < 0 写串口失败
result >=0  写串口成功，result的值是data的数据长度

3）注意：url中如果有特殊字符或中文需要转码

4）示例：
AFHTTPSessionManager *session = [AFHTTPSessionManager manager];
session.responseSerializer.acceptableContentTypes = [NSSet setWithObjects: @"text/plain", nil];
[session GET:@"http://192.168.0.66:80/write_comm.cgi?user=admin&pwd=&json=1length=2&data=%01%82" parameters:nil success:^(NSURLSessionDataTask *task, id responseObject) {
    
    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:responseObject  options:NSJSONReadingAllowFragments error:nil];
    //    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:[[NSData alloc] initWithBase64EncodedData:responseObject options:NSDataBase64DecodingIgnoreUnknownCharacters] options:NSJSONReadingAllowFragments error:nil];
    NSLog(@"success!result = %@",dic);
    
} failure:^(NSURLSessionDataTask *task, NSError *error) {
    
    NSLog(@"fail!error = %@",error);
    
}];