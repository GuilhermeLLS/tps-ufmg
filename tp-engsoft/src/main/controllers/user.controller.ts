export default class UserController {
  private userModel: any
  constructor(userModel: any) {
    this.userModel = userModel
  }

  public getUsers() {
    // ! TESTING
    return this.userModel.something
  }
}
