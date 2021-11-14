pipeline {
    agent none
    options {
        skipDefaultCheckout true
        timestamps()
    }


    environment {
        DOCKER_IMAGE = "csv2xls_jenkins_agent:0.0.3"
    }

    stages {
	    stage('Waiting for docker host agent'){
			agent {
				label 'windows_docker_host'
			}
            stages{
                stage('Download agent.jar'){
                    steps{
                        dir('C:/jenkinsagent'){
                            bat 'wget --no-clobber %JENKINS_URL%/jnlpJars/agent.jar'
                        }
                    }
                }
                stage('pulling docker image'){
                    steps{
                        bat 'echo "doing nothing at the moment"'
                        //docker pull sense_toolchain_win10_mingw
                    }
                }
                stage(' '){
                    environment{
                        BUILD_AGENT = "${env.NODE_NAME}_build_agent_${env.EXECUTOR_NUMBER}"
                    }
                    failFast true
                    parallel{
                        stage('Building'){
                            stages{
                                stage('[Build] starting agent'){
                                    steps{
                                        log_started()
                                        bat 'docker container ls'
                                        set_build_agent_secret()
                                        bat 'docker run -d --name %BUILD_TAG% --env BUILD_AGENT_SECRET -v C:/jenkinsagent:C:/jenkinsagent  --cpus=8 -m=16g --storage-opt "size=32GB" %DOCKER_IMAGE% java -jar C:/jenkinsagent/agent.jar -jnlpUrl %JENKINS_URL%/computer/%BUILD_AGENT%/jenkins-agent.jnlp -secret %BUILD_AGENT_SECRET% -workDir "C:/jenkins"'
                                        log_finished()
                                    }
                                }
                                stage('[Build] Waiting for agent') {
                                    agent {
                                        label env.BUILD_AGENT
                                    }
                                    stages {
                                        stage('[Build] Checking out source') {
                                            options {timeout(activity: true, time: 60)}
                                            steps {clone_repositories()}
                                        } //stage('Checking out source')
                                        stage('[Build] Preparing build directory') {
                                            options {timeout(activity: true, time: 30)}
                                            steps {prepare_build_directory()}
                                        } //stage('Preparing build directory')
                                        stage('[Build] build'){
                                            options {timeout(activity: true, time: 120)}
                                            steps{
                                                dir('b'){
                                                    bat "echo 'do nothing'"
//                                                    bat "cmake --build ."
                                                }
                                            }
                                        }
//                                       stage ('[Build] Generate Coverage report') {
//                                           steps{generate_coverage_report()}
//                                       }
//                                        stage('[Build] Analyse gcc output'){
//                                            steps{
//                                                recordIssues tool:gcc()
//                                            }
//                                        }
                                       stage('Run static analysis'){
                                        steps{
                                            log_started()
                                            dir('b'){
                                                bat "cmake --build . --target run_static_analysis"
                                                archiveArtifacts artifacts: "compile_commands.json"
                                            }
                                            log_finished()

                                        }
                                       }
                                       stage('Parse static analysis report'){
                                        steps{
                                            log_started()
                                            dir('b'){
                                                bat "cmake --build . --target parse_static_analysis_report"
                                            }
                                            log_finished()

                                        }
                                       }
                                      stage('Archiving static analysis report'){
                                            steps{
                                                log_started()
                                                dir('b') {
                                                    archiveArtifacts artifacts: "static_analysis_report.txt"
                                                }
                                                log_finished()
                                            }
                                        }
                                       stage('report static analysis'){
                                        steps{
                                            log_started()
                                                recordIssues tool:analysisParser('code-checker')
                                                //, pattern: 'b/static_analysis_report.txt', name: 'Codechecker'
                                            log_finished()

                                        }
                                       }
                                        stage('[Build] Archiving build log'){
                                            steps{
                                                log_started()
                                                dir('b') {
                                                    archiveArtifacts artifacts: ".ninja_log"
                                                }
                                                log_finished()
                                            }
                                        }
                                    } //stages
                                } //stage('Building stage')
                            }
                            post{
                                always{
                                    log_started()
                                    disconnectAgent(env.BUILD_AGENT)
//                                    bat 'docker container stop %BUILD_TAG%'
//                                    sleep(time: 10)
                                      bat 'docker container rm --force  %BUILD_TAG%'
                                    log_finished()
                                }
                            }
                        }
//                        stage('Running cppcheck'){
//                            environment{
//                                CPPCHECK_AGENT = "${env.NODE_NAME}_cppcheck_agent_${env.EXECUTOR_NUMBER}"
//                            }
//                            stages{
//                                stage('[Cppcheck] starting agent'){
//                                    steps{
//                                        log_started()
//                                        bat 'docker container ls'
//                                        set_cppcheck_agent_secret()
//                                        sleep(time: 10)
//                                        bat 'docker run -d --name %BUILD_TAG%_CPPCHECK --env CPPCHECK_AGENT_SECRET -v C:/jenkinsagent:C:/jenkinsagent  --cpus=1 -m=4g %DOCKER_IMAGE% java -jar C:/jenkinsagent/agent.jar -jnlpUrl %JENKINS_URL%/computer/%CPPCHECK_AGENT%/jenkins-agent.jnlp -secret %CPPCHECK_AGENT_SECRET% -workDir "C:/jenkins"'
//                                        log_finished()
//                                    }
//                                }
//                                stage('[Cppcheck] Waiting for agent') {
//                                    agent {
//                                        label env.CPPCHECK_AGENT
//                                    }
//                                    stages {
//                                        stage('[Cppcheck] Checking out source') {
//                                            options {timeout(activity: true, time: 60)}
//                                            steps {clone_repositories()}
//                                        } //stage('Checking out source')
//                                        stage('[Cppcheck] Preparing build directory') {
//                                            options {timeout(activity: true, time: 10)}
//                                            steps {prepare_build_directory()}
//                                        } //stage('Preparing build directory')
//                                        stage('[Cppcheck] run cppcheck'){
//                                            options {timeout(activity: true, time: 120)}
//                                            steps{run_cppcheck()}
//                                        }
//                                        stage('[Cppcheck] publish results'){
//                                              steps{
//                                                    log_started()
//                                                    dir('b') {
//                                                        bat 'C:/msys64/msys2_shell.cmd -defterm  -no-start -full-path -here  -c "../docker/fix_paths_in_cppcheckresult.sh cppcheckresult.xml > cppcheckresult_fixed_paths.xml"'
//                                                        bat "xsltproc ../jenkins/cleanup_cppcheck.xsl cppcheckresult_fixed_paths.xml > cppcheckresult_fixed_paths_filtered.xml"
//                                                    }
//                                                    recordIssues enabledForFailure: true, tool: cppCheck(pattern: 'b/cppcheckresult_fixed_paths_filtered.xml')
//                                                    log_finished()
//                                             }
//                                        }
//                                        stage('[Cppcheck] Archiving result'){
//                                            steps{
//                                                log_started()
//                                                dir('b') {
//                                                    archiveArtifacts artifacts: "cppcheckresult.xml"
//                                                }
//                                                log_finished()
//                                            }
//                                        }
//                                    } //stages
//            //						post{
//            //							always{
//            //								dir('b') {
//            //										recordIssues enabledForFailure: true, tool: cppCheck(pattern: 'cppcheckresult.xml')
//            //								}
//            //							}
//            //						}
//                                } //stage('Building stage')
//                            }
//                            post{
//                                always{
//                                    log_started()
//                                    disconnectAgent(env.CPPCHECK_AGENT)
////                                    bat 'docker container stop %BUILD_TAG%_CPPCHECK'
////                                    sleep(time: 10)
//                                    bat 'docker container rm  --force  %BUILD_TAG%_CPPCHECK'
//                                    log_finished()
//                                }
//                            }
//                        }
                    }
                }
            }
        }

    } //stages

} //pipeline

import groovy.json.JsonSlurper



def setCMakeArguments() {
    env.CMAKE_ARGUMENTS = "\
            -GNinja \
            -DCMAKE_BUILD_TYPE=RelWithDebInfo \
            -DCMAKE_PREFIX_PATH=C:/msys64/mingw64"

    env.SOURCE_DIRECTORY = '..'
}




def log_started() {
    println "====================================================================================================================================================================\n${STAGE_NAME} ...\n--------------------------------------------------------------------------------------------------------------------------------------------------------------------"
}


def log_finished() {
    println "--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n${STAGE_NAME} finished!\n===================================================================================================================================================================="
}


def clone_repositories(){
    log_started()
    checkout scm
    log_finished()
}

def prepare_build_directory(){
    log_started()
    setCMakeArguments()
    dir('b') {
        deleteDir()
    }
    dir('b') {
        powershell """
            "---------------------------------------------------------------------------------"
            "BUILD NUMBER: ${env.BUILD_NUMBER}"
            "BUILD TAG   : ${env.BUILD_TAG}"
            "BUILD TYPE  : ${env.BUILD_TYPE}"
            "---------------------------------------------------------------------------------"
        """
            bat "cmake ${env.CMAKE_ARGUMENTS} ${env.SOURCE_DIRECTORY}"
    }
    log_finished()
}

def build_and_run_tests(){
    log_started()
    dir('b') {
        // in docker some timezone related unit tests fail
        // to exclude them, set the following environment:
        // UNIT_TEST_PARAMETERS=--gtest_filter=-*fromLocalToUtc*:CoreDivaDateTime.toUtcDateTimeAmbiguousDateTimePolicy:CoreDivaDateTime.LocalToUTCConversion
        bat "cmake --build ."
    }
    log_finished()
}
def run_cppcheck(){
    log_started()
    dir('b') {
        bat "${env.SOURCE_DIRECTORY}/docker/runcppcheck.bat"
    }
    log_finished()
}

def generate_coverage_report(){
    log_started()
    dir('b') {
        bat 'gcovr --root .. . -x -o coverage.xml'
    }
    cobertura coberturaReportFile: 'b/coverage.xml'
    log_finished()
}

def set_build_agent_secret(){
    def build_agent_secrets = "${BUILD_AGENT_SECRETS}".split(' ')
    def index = "${env.EXECUTOR_NUMBER}" as Integer
    env.BUILD_AGENT_SECRET = build_agent_secrets[index]
}
def set_cppcheck_agent_secret(){
    def cppcheck_agent_secrets = "${CPPCHECK_AGENT_SECRETS}".split(' ')
    def index = "${env.EXECUTOR_NUMBER}" as Integer
    env.CPPCHECK_AGENT_SECRET = cppcheck_agent_secrets[index]
}

def disconnectAgent(agent){
    Jenkins.instance.getNode(agent).getComputer().disconnect()
}
