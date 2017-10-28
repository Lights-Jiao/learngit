<?php
/**
 * Created by IntelliJ IDEA.
 * User: lights
 * Date: 2016/11/30
 * Time: 下午8:22.
 */

/*
 * 对反射的一些应用
 * 应用场景为：创建一个类，动态调用Module对偶像，既该类可以自由加载第三方插件并集成近已有的系统，而不需要把第三方的代码硬编码进原有的代码。
 * 要达到这个目的，可以在Module接口 或者 抽象类中定义一个统一的方法（例如execute()方法），强制要求所有的子类都要事先这个方法
 * 用户在外部用xml配置文件中列出所有的Module，系统可以使用xml提供的信息来加载一定数目的Module，然后调用execute方法
 */

/**
 * 提供其他接口调用的入参的基础类
 * Class Person.
 */
class Person
{
    public $name;

    public function __construct($name)
    {
        $this->name = $name;
    }
}

/**
 * 统一的接口
 * Interface Module.
 */
interface Module
{
    public function execute();
}

/**
 * 第一个类
 * Class FtpModule.
 */
class FtpModule implements Module
{
    public function setHost($host)
    {
        echo "FtpModule::setHost():$host\n";
    }

    public function setUser($user)
    {
        echo "FtpModule::setUser():$user\n";
    }

    public function execute()
    {
        echo "FtpModule::execute()..........\n";
    }
}

/**
 * 第二个类
 * Class PersonModule.
 */
class PersonModule implements Module
{
    public function setPerson(Person $person)
    {
        echo "PersonModule::setPerson():$person->name\n";
    }

    public function execute()
    {
        echo "PersonModule::execute()..........\n";
    }
}

/**
 * 最核心的部分，通过这一个类，使用后反射去调用上面两个类的方法，而不是直接的调用上面的类
 * Class ModuleRunner.
 */
class ModuleRunner
{
    /**
     * @var array 假装是配置信息
     */
    private $configData = [
        'PersonModule' => ['person' => 'bob'],
        'FtpModule' => [
            'host' => 'www.baidu.com',
            'user' => 'jack',
        ],
    ];

    /**
     * @var array 保存各个Module
     */
    private $modules = [];

    /**
     * 逐个的调用配置中的类 及其 所有方法.
     *
     * @throws Exception
     */
    public function init()
    {
        $interface = new ReflectionClass('Module');

        foreach ($this->configData as $moduleName => $params) {
            $moduleClass = new ReflectionClass($moduleName);

            // if (!$moduleClass->implementsInterface('Module')) {
            if (!$moduleClass->isSubclassOf($interface)) {
                throw new Exception("unknow module type :$moduleName");
            }

            $moduleInstance = $moduleClass->newInstance();
            foreach ($moduleClass->getMethods() as $method) {
                $this->handleMethod($moduleInstance, $method, $params);
            }
            $this->modules[] = $moduleInstance;
        }
    }

    /**
     * 具体的方法的调用.
     *
     * @param $instance Module
     * @param $method   ReflectionMethod
     * @param $params   array
     *
     * @return bool
     *
     * @throws Exception
     */
    public function handleMethod($instance, $method, $params)
    {
        $methodName = $method->getName();
        $expectArgs = $method->getParameters();

        if (1 != count($expectArgs) || 'set' != substr($methodName, 0, 3)) {
            return false;
        }

        $property = strtolower(substr($methodName, 3));
        if (!isset($params[$property])) {
            return false;
        }

        $argClass = $expectArgs[0]->getClass();
        if (empty($argClass)) {
            $method->invoke($instance, $params[$property]);
        } else {
            $method->invoke($instance, $argClass->newInstance($params[$property]));
        }

        return true;
    }

    /**
     * 使用反射批量调用 对象的execute方法.
     */
    public function executeModules()
    {
        foreach ($this->configData as $moduleName => $params) {
            $moduleClass = new ReflectionClass($moduleName);
            $executeMethod = $moduleClass->getMethod('execute');
            $executeMethod->invoke($moduleClass->newInstance());
        }
    }
}

/**
 * main 函数.
 */
function main()
{
    $test = new ModuleRunner();
    $test->init();
    $test->executeModules();
}

main();
